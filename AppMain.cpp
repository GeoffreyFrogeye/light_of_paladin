#include "AppMain.h"
#include "Eau.h"
#include "Lumiere.h"
#include "GestionnaireID.h"
#include "ExceptionPerso.h"
#include "InputListener.h"
#include "GestionnaireTerrain.h"
#include "CeguiMgr.h"

#include <SkyX.h>
#include <OgreTerrainGroup.h>
#include <PagedGeometry.h>
#include <BatchPage.h>
#include <ImpostorPage.h>
#include <TreeLoader3D.h>

#include <boost/thread.hpp>

#include <Common/Base/hkBase.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>

#ifdef _DEBUG

#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

#endif

using namespace Ogre;

AppMain::AppMain()
{
	mpRoot = nullptr;
	mpWindow = nullptr;
	mpSceneMgr = nullptr;
	mpCam = nullptr;
	mpSky = nullptr;
	mpTerrain = nullptr;
	mpWater = nullptr;
	mpTrees = nullptr;
	mpWater = nullptr;
	mpCam = nullptr;
	mpCeguiMgr = nullptr;
	mpHkWorld = nullptr;

	std::srand(time(nullptr));
}

AppMain::~AppMain()
{
	if (mpTrees != nullptr && mpTrees->getPageLoader() != nullptr)
	{
		delete mpTrees->getPageLoader();
		delete mpTrees;
		mpTrees = nullptr;
	}

	if (mpWater != nullptr)
	{
		delete mpWater;
		mpWater = nullptr;
	}

	if (mpLum != nullptr)
	{
		delete mpLum;
		mpLum = nullptr;
	}

	if (mpTerrain != nullptr)
	{
		delete mpTerrain;
		mpTerrain = nullptr;
	}
	if (mpCeguiMgr != nullptr)
	{
		delete mpCeguiMgr;
		mpCeguiMgr = nullptr;
	}

	if (mpHkWorld != nullptr && mpHkWorld->getReferenceCount() > 0)
	{
		mpHkWorld->removeReference();
		mpHkWorld = nullptr;
	}
	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();

	if(mpRoot != nullptr)
	{
		delete mpRoot;
		mpRoot = nullptr;
	}	

	/* Destruction des singletons */
	GestionnaireID::destroy();
}

void AppMain::start()
{
	if(!initOGRE()) //D�marrage de Ogre
	{
		throw ExceptionPerso("Erreur dans AppMain::initOGRE(), mais Ogre ne parait pas avoir lev� une exception.", FATAL);
	}

	if (!initHavok()) //Physique et collision
	{
		throw ExceptionPerso("Erreur lors de l'initialisation du moteur Havok.", FATAL);
	}

	if (!createBase())
	{
		throw ExceptionPerso("Erreur lors de la cr�ation des �l�ments basiques du rendu", FATAL);
	}

	mpCeguiMgr = new CeguiMgr();

	InputListener *pListener = new InputListener(mpWindow, mpCam, mpCeguiMgr);   //Ecouteur d'�v�nement pour les entr�es utilisateurs
	mpRoot->addFrameListener(pListener);

	/* Cr�ation du singleton gestionnaire ID */
	GestionnaireID::getInstance();

	if(!createScene())  //Cr�ation de la sc�ne
	{
		throw ExceptionPerso("Erreur lors de la cr�ation de la sc�ne.", ERREUR);
	}

	infiniteLoop(); //Boucle de rendu
}

bool AppMain::initOGRE()
{
	Ogre::ConfigFile config;    //Gestionnaire de fichier de config Ogre

#ifdef _DEBUG
	mpRoot = new Root("plugins_d.cfg", "ogre.cfg", "Ogre_d.log");
	config.load("resources_d.cfg");
#else
	mpRoot = new Root("plugins.cfg", "ogre.cfg", "Ogre.log");
	config.load("resources.cfg");
#endif

	ConfigFile::SectionIterator sectionI = config.getSectionIterator();

	String archName, secName, typeName;

	while (sectionI.hasMoreElements())  //Tant qu'il reste des sections � lire
	{
		secName = sectionI.peekNextKey();
		ConfigFile::SettingsMultiMap *pSettingsMap = sectionI.getNext();
		ConfigFile::SettingsMultiMap::iterator i;

		/* On ajoute toutes les ressources */
		for (i=pSettingsMap->begin(); i != pSettingsMap->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;

			ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	/* Si on ne parvient pas � charger un fichier de config pour l'API de rendu, ni � lancer le dialogue de configuration, on quitte */
	if (!(mpRoot->restoreConfig() || mpRoot->showConfigDialog()))
	{
		return false;
	}

	/* Initialise la fen�tre de rendu avec son titre */
	mpWindow = mpRoot->initialise(true, "Projet SAM");

	/* Niveau de mipMap (1x1x1) */
	TextureManager::getSingleton().setDefaultNumMipmaps(MIP_UNLIMITED);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups(); //On charge tout et on calcule les niveaux de mipMap

	/* Cr�ation du sc�ne manager */
	mpSceneMgr = mpRoot->createSceneManager(ST_EXTERIOR_FAR, "SceneManager");

	/* Activation du filtrage anisotropique, niveau 8 */
	MaterialManager::getSingleton().setDefaultTextureFiltering(TFO_ANISOTROPIC);
	MaterialManager::getSingleton().setDefaultAnisotropy(8);

	return true;
}

bool AppMain::createScene()
{
	if(!(createSky() && createTerrain() && createLight() && createObject() && createPersonnage()))
	{
		return false;
	}

	return true;
}

bool AppMain::createBase()
{
	mpSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_ADDITIVE_INTEGRATED);

	mpCam = mpSceneMgr->createCamera("Camera");
	mpCam->setPosition(Vector3(0.0, 10.0, 0.0));
	mpCam->lookAt(Vector3(10.0, 10.0, 10.0));
	mpCam->setNearClipDistance(2.0f);
	mpCam->setCastShadows(false);

	if (mpRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
	{
		mpCam->setFarClipDistance(50000);
	}
	else
	{
		mpCam->setFarClipDistance(25000);
	}

	Viewport *vp = mpWindow->addViewport(mpCam);
	vp->setBackgroundColour(ColourValue(0.0, 0.0, 0.0, 1.0));
	mpCam->setAspectRatio(vp->getActualWidth()/Real(vp->getActualHeight()));

	return true;
}

bool AppMain::createSky()
{
	mpSky = new SkyX::SkyX(mpSceneMgr, new SkyX::BasicController());
	mpSky->create();

	mpRoot->addFrameListener(mpSky);
	mpWindow->addListener(mpSky);

	// Couche de nuages basique
	mpSky->getCloudsManager()->add(SkyX::CloudLayer::Options());

	mpSky->getMoonManager()->setMoonSize(0.3f);

	mpSky->setTimeMultiplier(0.02f);

	return true;
}

bool AppMain::createTerrain()
{
	Light *pSoleil = mpSceneMgr->createLight("soleil");
	pSoleil->setType(Light::LT_DIRECTIONAL);
	pSoleil->setDirection(Vector3(0.0f, -1.0f, 3.0f));
	pSoleil->setDiffuseColour(ColourValue(0.8f, 0.68f, 0.73f));
	pSoleil->setSpecularColour(ColourValue(0.8f, 0.68f, 0.73f));

	mpTerrain = new GestionnaireTerrain(TAILLE_IMG_HEIGHTMAP, TAILLE_MONDE, mpSceneMgr, mpSceneMgr->getLight("soleil"), mpCam, mpCam->getViewport(), mpRoot, mpHkWorld);

	//boost::thread ThTerrainCreationHavok(&AppMain::createTerrainHavokMultiThreaded, this);

	mpRoot->addFrameListener(mpTerrain->getPtrChunk());

	mpWater = new Eau(mpSceneMgr, mpCam, mpWindow->getViewport(0), mpSky);
	mpRoot->addFrameListener(mpWater);

	mpWater->setHauteur(0.0f);

	// Create water
	mpWater->create();

	mpTrees = new Forests::PagedGeometry();

	mpTrees->setCamera(mpCam);
	mpTrees->setPageSize(50);
	mpTrees->setBounds(Forests::TBounds(0, 0, 10000, 10000));

	mpTrees->addDetailLevel<Forests::BatchPage>(500, 50);
	mpTrees->addDetailLevel<Forests::ImpostorPage>(1000, 100);

	//Create a new TreeLoader3D object first
	Forests::TreeLoader3D *treeLoader = new Forests::TreeLoader3D(mpTrees, Forests::TBounds(0, 0, 10000, 10000));

	Entity *pEnt1 = mpSceneMgr->createEntity("tree", "arbre.mesh"), *pEnt2 = mpSceneMgr->createEntity("lila", "lila.mesh"), *pEnt3 = mpSceneMgr->createEntity("apple tree", "pommier.mesh");

	Entity* vege[] = {pEnt1, pEnt2, pEnt3};

	float x, y, z, yaw, scale;
	int t;
	for (int i = 0; i < 100; i++){
		yaw = Math::RangeRandom(0.0f, 360.0f);
		x = Math::RangeRandom(0.0f, 10000.0f);
		z = Math::RangeRandom(0.0f, 10000.0f);
		scale = Math::RangeRandom(0.2f, 0.9f);
		t = static_cast<int>(Math::RangeRandom(0, 3));
		y = mpTerrain->getTerrains()->getTerrain(0, 0)->getHeightAtWorldPosition(x, 5000.0f, z);

		if(y > 300.0f)
		{
			treeLoader->addTree(vege[t], Vector3(x, y, z), Degree(yaw), scale);
		}
	}

	mpTrees->setPageLoader(treeLoader);

	return true;
}

bool AppMain::createObject()
{

	return true;
}

bool AppMain::createPersonnage()
{
	Entity *pEnt1 = mpSceneMgr->createEntity("pingouin", "penguin.mesh");
	SceneNode *pNodePeng = mpSceneMgr->getRootSceneNode()->createChildSceneNode("nodePengouin", Vector3(100.0f, 550.0f, 100.0f));
	pNodePeng->attachObject(pEnt1);

	Entity *pEnt2 = mpSceneMgr->createEntity("rylai", "rylai.mesh");
	SceneNode *pNodeRylai = pNodePeng->createChildSceneNode("nodeRylai", Vector3(-23.0f, 8.0f, 20.0f));
	pNodeRylai->pitch(Degree(45.0f));
	pNodeRylai->scale(Vector3(10.0, 10.0, 10.0));
	pNodeRylai->attachObject(pEnt2);

	Entity *pEnt3 = mpSceneMgr->createEntity("tux", "palace.mesh");
	SceneNode *pNodeTux = mpSceneMgr->getRootSceneNode()->createChildSceneNode("nodeTux", Vector3(200.0f, 500.0f, 200.0f));
	pNodeTux->setScale(100.0f, 100.0f, 100.0f);
	pNodeTux->attachObject(pEnt3);

	ParticleSystem* sunParticle = mpSceneMgr->createParticleSystem("Boule de feu", "Particule/FireBall");
	SceneNode* particleNode = pNodePeng->createChildSceneNode("ParticleFire");
	particleNode->attachObject(sunParticle);
	particleNode->setPosition(0, 30, 0);

	int stat[ESTATMAX]={0};
	ajoutPersonnage(pNodePeng, "Samuel", stat, 1, 0, Vector3(0.0f), Vector3(0.0f));

	return true;
}

bool AppMain::createLight()
{
	mpLum = new GestionnaireLight(mpSceneMgr, mpSceneMgr->getLight("soleil"), mpSky, mpWater, ColourValue(0.8f, 0.8f, 0.8f));

	mpRoot->addFrameListener(mpLum);

	return true;
}

void AppMain::infiniteLoop()
{
	Personnage *pSam = nullptr;
	bool bSens = true;


	/* test */
	try
	{
		pSam = getPersonnage("Samuel");
	}
	catch(std::exception& e)
	{
		e.what();
	}
	/* test */

#ifdef _DEBUG
	hkpPhysicsContext* physicsContext = new hkpPhysicsContext;
	physicsContext->addWorld(mpHkWorld);

	hkpPhysicsContext::registerAllPhysicsProcesses();

	hkArray<hkProcessContext*> contexts;
	contexts.pushBack( physicsContext );
	hkVisualDebugger* vdb = new hkVisualDebugger( contexts );

	vdb->serve(25001);
#endif

	while (true)
	{
		mpHkWorld->stepDeltaTime(0.001);

#ifdef _DEBUG
		vdb->step(0);
#endif

		WindowEventUtilities::messagePump();

		if (!mpRoot->renderOneFrame())
		{
			return;
		}

		mpTrees->update();
	}
}

bool AppMain::ajoutPersonnage(Ogre::SceneNode *pNoeud, std::string const& nom, int stat[EStat::ESTATMAX], int niveau, int XP, Ogre::Vector3 const& position, Ogre::Vector3 const& rotation)
{
	//Personnage *pPersonnage =  new Personnage(pNoeud, stat, true, nom, niveau, XP);

	std::pair<std::map<std::string, Personnage*>::iterator, bool> retVal;

	//retVal = mmapPersonnages.insert(std::pair<std::string, Personnage*>(nom, pPersonnage));

	return retVal.second;
}

Personnage* AppMain::getPersonnage(std::string const& nom) const
{
	std::map<std::string, Personnage*>::const_iterator it;
	it = mmapPersonnages.find(nom);

	if (it != mmapPersonnages.end())
	{
		return it->second;
	}
	else
	{
		std::string mesg = nom+": "+"Ce personnage n'existe pas. Op�ration abandonn�e.";
		throw ExceptionPerso(mesg.c_str(), INFO);
	}
}

