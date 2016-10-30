#include "Game.h"
#include "Controls.h"
#include "TirFactory.h"

using namespace PewPew;

/// <summary>
/// Constructeur de la classe Game
/// </summary>
Game::Game() : 
	mainWin(VideoMode(LARGEUR, HAUTEUR, 32), "Pew Pew!"), view(mainWin.getDefaultView()), fond(5), thrust(0), 
	mouvementJoueur(0, 0)/*,leftClick(false), rightClick(false)*/, compteurEnnemi(0),compteurObstacle(0), gameOver(false),
	frames(0), canSwitch(true)
{ 
	srand(time(NULL));

	vaisseauJoueur = Joueur::GetInstance();
	prochainVaisseau = rand() % 50 + 15;
	prochainObstacle = rand() % 300 + 15;

	for (int i = 0; i < NBR_VAISSEAUX; i++)
		ennemis[i] = nullptr;

	for (int i = 0; i < NB_MAX_OBSTACLE; i++)
		obstacles[i] = nullptr;

	Evantail::InitDirections();	ui = nullptr;
}
/// <summary>
/// Destructeur de la classe Game
/// </summary>
Game::~Game()
{
	// Suppression des ennemis
	for (int i = 0; i < NBR_VAISSEAUX; i++)
	{
		if (ennemis[i] != nullptr)
		{
			delete ennemis[i];
			ennemis[i] = nullptr;
		}

	}
	// Suppression des tirs
	for (int i = 0; i < NB_MAX_TIRS; i++)
	{
		if (tirs[i] != nullptr)
		{
			delete this->tirs[i];
			tirs[i] = nullptr;
		}

	}
	// Suppression des bonus
	for (int i = 0; i < MAX_NB_BONUS; i++)
	{
		if (listeBonus[i] != nullptr)
		{
			delete listeBonus[i];
			listeBonus[i] = nullptr;
		}
	}
	// Suppression du joueur
	vaisseauJoueur->Release();
	vaisseauJoueur = nullptr;

	// Suppression de l'interface 
	if (ui != nullptr)
		delete ui;

	// Suppression des éléments de l'Evantail
	for (int i = 0; i < Evantail::NB_SHOTS; i++)
	{
		if (Evantail::directions[i] != nullptr)
		{
			delete Evantail::directions[i];
			Evantail::directions[i] = nullptr;
		}
	}

	// Suppression des obstacles
	for (int i = 0; i < NB_MAX_OBSTACLE; i++)
	{
		if (obstacles[i] != nullptr)
			delete obstacles[i];
	}

	// Suppression du boss
	if (this->boss != nullptr)
	{
		delete boss;
	}

}
/// <summary>
/// Initialise le jeu, affiche les écrans de début et de fin et exécute la boucle principale de jeu
/// </summary>
/// <returns>EXIT_FAILURE si le jeu ne peut pas s'initialiser, EXIT_SUCCESS si tout s'est bien déroulé</returns>
int Game::Run()
{
	// Initialise le jeu 
	if (!Init())
	{
		return EXIT_FAILURE;
	}
	// Part la musique de fond 
	SoundPlayer::Update();
	// Affiche l'écran de début tant que le joueur n'appuie par sur "Enter"
	while (mainWin.isOpen()&& !Keyboard::isKeyPressed(Keyboard::Return))
	{
		mainWin.draw(ecran.GetBackground());
		mainWin.display();
	}
	// Boucle principale de jeu
	while (mainWin.isOpen() && !gameOver)
	{
		GetInputs();
		Update();
		Draw();
	}
	// Change pour l'écran de fin de partie
	ecran.SwitchBackground();
	// Arrête la musique de jeu et part la musique de défaite
	SoundPlayer::StopPlayingBGMusic();
	SoundPlayer::PlaySound("The Choice");
	// Affiche l'écran de fin de partie tant que le joueur n'appuie par sur "Enter"
	while (mainWin.isOpen() && !Keyboard::isKeyPressed(Keyboard::Return))
	{
		mainWin.draw(ecran.GetBackground());
		UI::AfficherScore(&mainWin);
		mainWin.display();
	}

	return EXIT_SUCCESS;
}

/// <summary>
/// Appelle les méthodes d'initialisation de toutes les classes et initialise le joueur
/// </summary>
/// <returns>Vrai si tout est correctement initialisé, faux sinon</returns>
bool Game::Init()
{
	mainWin.setVerticalSyncEnabled(true);
	mainWin.setFramerateLimit(60);

	// Chargement du fond d'écran
	if (!fond.SetTexture("Sprites\\test.jpg"))
	{
		return false;
	}
	// Chargement de la texture du joueur
	if (!shipT.loadFromFile("Sprites\\ship.png"))
	{
		return false;
	}
	// Chargement des textures de tous les ennemis
	if (!Ennemi::LoadShips())
	{
		return false;
	}
	// Chargement des textures de tous les bonus
	if (!Bonus::LoadAllTextures())
	{
		return false;
	}
	// Chargement de la texture des tirs
	if (!tirT.loadFromFile("Sprites\\tirEnnemi.png"))
		return false;
	// Chargement des éléments de l'interface utilisateur
	if (!UI::InitGraphiques())
		return false;
	// Chargement des textures des obstacles
	if (!Obstacle::Init())
		return false;
	// Chargement de tous les sons et musiques
	if (!SoundPlayer::Init())
		return false;
	// Chargement des écrans de début et de fin
	if (!ecran.Init())
		return false;

	ui=new UI();
	Subject::Add_Observer(ui);

	// Initialisation du vaisseau joueur
	vaisseauJoueur->setTexture(shipT);
	vaisseauJoueur->setPosition(200, HAUTEUR/2);
	vaisseauJoueur->InitGraphiques();

	Subject::CreerArmeObservers(this->vaisseauJoueur, this->ui);
	return true;
}

void Game::GetInputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (mainWin.pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			mainWin.close();
		}
	}

	Controls::moveUp = Keyboard::isKeyPressed(Keyboard::Up);
	Controls::moveLeft = Keyboard::isKeyPressed(Keyboard::Left);
	Controls::moveRight = Keyboard::isKeyPressed(Keyboard::Right);
	Controls::moveDown = Keyboard::isKeyPressed(Keyboard::Down);

	Controls::tir = Keyboard::isKeyPressed(Keyboard::Space);
	Controls::changerArme = Keyboard::isKeyPressed(Keyboard::Return);

	Controls::quit = Keyboard::isKeyPressed(Keyboard::Escape);
}

/// <summary>
/// Met à jour tous les éléments du jeu.
/// </summary>
void Game::Update()
{
	//Met à jour les cadences de tirs des armes (décrémente leur variables 'peutTirer').
	this->vaisseauJoueur->UpdateCadences();
	frames++;
	//Si 10 frames se sont passées depuis la dernière fois que je joueur a changé d'arme, indique qu'il peut le faire à nouveau (évite de changer d'arme tellement vite que tu revient à l'arme que t'avais avant d'avoir changé).
	if (frames % 10 == 0)
		canSwitch = true;
	//Ferme le jeu si la touche escape est appuyée.
	if (Controls::quit)
	{
		this->mainWin.close();
	}
	//Les flèches déplacent le joueur.
	if (Controls::moveLeft)
	{
		mouvementJoueur.x = -1;
		fond.SlowDown();
	}
	else if (Controls::moveRight)
	{
		mouvementJoueur.x = 1;
		fond.SpeedUp();
	}
	else
	{
		mouvementJoueur.x = 0;
		fond.ResetSpeed();
	}

	if (Controls::moveUp)
	{
		mouvementJoueur.y = -1;
		vaisseauJoueur->Monter();
	}
	else if (Controls::moveDown)
	{
		mouvementJoueur.y = 1;
		vaisseauJoueur->Descendre();
	}
	else
	{
		mouvementJoueur.y = 0;
		vaisseauJoueur->Centrer();
	}
	//La bar d'espace effectue un tir.
	if (Controls::tir)
	{
		for (int i = 0; i < NB_MAX_TIRS; i++)
		{
			if (this->tirs[i] == nullptr)
			{
				//Crée le tir selon l'arme active,
				Tir* t = this->vaisseauJoueur->tirer();
				if (t != nullptr)
				{
					//initialise le tir,
					t->Init(this->tirT);
					// Le joueur a tiré, un son joue 
					SoundPlayer::PlaySound("tirJoueur");
					//si c'est un tir chercheur, lui précise sa cible,
					if (typeid(*t) == typeid(TirChercheur))
					{
						TirChercheur* tC = (TirChercheur*)t;
						for (int j = 0; j < NBR_VAISSEAUX; j++)
						{
							if (this->ennemis[j] != nullptr)
								tC->SetCible(this->ennemis[j]);
						}
						if (tC->GetCible() == nullptr)
						{
							delete t;
							t = nullptr;
						}
					}
				}
				//puis l'ajoute à la liste des tirs.
				this->tirs[i] = t;
				break;
			}
		}
	}

	//Change l'arme active du joueur.
	if (Controls::changerArme)
	{
		if (canSwitch)
			if (this->vaisseauJoueur->ChangerArme())
				this->canSwitch = false;
	}

	//Générer de nouveaux ennemis
	GenererEnnemi();
	// Générer de nouveaux obstacles
	GenererObstacle();
	// Faire bouger tous les éléments: fond, joueur et ennemis 
	MovementUpdate();
	// Gérer la liste de bonus actifs
	BonusUpdate();
	// Gérer les collisions de projectiles
	ProjectileUpdate();
	for (int i = 0; i < NBR_VAISSEAUX; i++)
	{
		if (ennemis[i] != nullptr && ennemis[i]->GetPV()<=0)
		{ 
			int generer = rand() % 3;
			if (generer == 0)
			{
				GenererBonus(ennemis[i]);
			}
			Subject::Remove_Observer(ennemis[i]);
			delete ennemis[i];
			ennemis[i] = nullptr;
		}
	}
	// Gérer les collisions avec les obstacles
	ObstacleUpdate();
	// Gérer la fin de partie
	if (vaisseauJoueur->GetPV() <= 0)
	{
		gameOver = true;
	}
	// Mettre à jour l'interface
	UI::SetVies(vaisseauJoueur->GetPV());
	if (vaisseauJoueur->GetPremierBouclier() != nullptr)
		UI::SetBouclier(vaisseauJoueur->GetPremierBouclier()->GetPV());
	// Mettre à jour l'environnement sonore
	SoundPlayer::Update();
}

/// <summary>
/// Ajoute le tir spécifié en paramètre à la liste des tirs.
/// </summary>
/// <param name="_newTir">Le tir à ajouter.</param>
void Game::AddShot(Tir* _newTir)
{
	//Permet d'indique si le tir a pu être ajouté.
	bool tirAjouter = false;

	//Si le tir n'est pas null,
	if (_newTir != nullptr)
	{
		for (int i = 0; i < NB_MAX_TIRS; i++)
		{
			if (this->tirs[i] == nullptr)
			{
				//l'initialiser, puis l'ajouter.
				_newTir->Init(this->tirT);
				this->tirs[i] = _newTir;
				tirAjouter = true;
				SoundPlayer::PlaySound("tirEnnemi");
				break;
			}
		}
	}

	//Si le tir n'a pas pu être ajouté, le delete.
	if (!tirAjouter)
		delete _newTir;
}

/// <summary>
/// Met à jour les mouvement de tous les éléments du jeu.
/// </summary>
void Game::MovementUpdate()
{
	//Déplace le background.
	fond.Move(thrust);
	//Déplace le vaisseau du joueur.
	vaisseauJoueur->MouvementJoueur(mouvementJoueur);
	int isShooting = 0;
	//Déplace tous les vaisseaux ennemis.
	for (int i = 0; i < NBR_VAISSEAUX; i++)
	{
		if (ennemis[i] != nullptr)
		{
			//Vérifie si le vaisseau est entrer en collision avec le joueur.
			if (ennemis[i]->VerifierCollisionAvecJoueur(vaisseauJoueur->GetRect()))
			{
				//Si les pv du joueur sont plus grand que ceux de l'ennemis,
				if (vaisseauJoueur->GetPV() >= ennemis[i]->GetPV())
				{
					//endommager le joueur du nombre de pv de l'ennemi,
					vaisseauJoueur->InfligerDegats(ennemis[i]->GetPV());
					// Dropper un bonus
					GenererBonus(ennemis[i]);
					//mettre à jour le score,
					Joueur::AjouterScore(ennemis[i]->GetPoints());
					//enlever l'ennemi des observeurs,
					Bonus::Remove_Observer(ennemis[i]);
					//delete l'"ennemi
					delete ennemis[i];
					ennemis[i] = nullptr;
					//et mettre à jour l'ui.
					UI::SetPoints(vaisseauJoueur->GetScore());
				}
				//sinon, faire les dommages au joueur.
				else
				{
					ennemis[i]->InfligerDegats(vaisseauJoueur->GetPV());
					// Joueur meurt
				}
			}
			// Mouvement selon le type de vaisseau ennemi
			//Si l'ennemi est toujours en vie,
			if (ennemis[i] != nullptr)
			{
				//le déplacer. Les types kamikaze et évantail ont une méthode plus spécifique de déplacement.
				if (typeid(*ennemis[i]) == typeid(Kamikaze))
				{
					Kamikaze* k = (Kamikaze*)ennemis[i];
					k->Mouvement(vaisseauJoueur->getPosition());
				}
				else if (typeid(*ennemis[i]) == typeid(BaseAmelioree))
				{
					BaseAmelioree* b = (BaseAmelioree*)ennemis[i];
					b->Mouvement(vaisseauJoueur->getPosition());
				}
				else
				{
					ennemis[i]->Mouvement();
				}

				 //Tir selon le type de vaisseau ennemi
				//Chaque ennemi a une méthode spécifique de tir.
				if (ennemis[i]->CanShoot())
				{
					if (typeid(*ennemis[i]) == typeid(BaseAmelioree))
					{
						isShooting = rand() % 500;

						if (isShooting < 7)
						{
							TirChercheur* t = (TirChercheur*)ennemis[i]->tirer();
							t->SetCible(this->vaisseauJoueur);
							this->AddShot(t);
						}
					}
					else if (typeid(*ennemis[i]) == typeid(Multishot))
					{
						isShooting = rand() % 100;

						if (isShooting < 1)
						{
							Multishot* tEnnemi = (Multishot*)ennemis[i];
							for (int k = -2; k < 3; k++)
							{
								this->AddShot(tEnnemi->tirer(k));
							}
						}
					}
					else if (typeid(*ennemis[i]) == typeid(Evantail))
					{
						isShooting = rand() % 200;

						if (isShooting <1)
						{
							Evantail* tEnnemi = (Evantail*)ennemis[i];
							for (int k = 0; k < 7; k++)
							{
								this->AddShot(tEnnemi->tirer(k));
							}
						}
					}
					else if (typeid(*ennemis[i]) == typeid(Base))
					{
						isShooting = rand() % 200;

						if (isShooting < 5)
						{
							Tir* t = this->ennemis[i]->tirer();
							this->AddShot(t);
						}
					}
				}	

				// Vérifier que le vaisseau ennemi est toujours dans les limites du jeu
				if (ennemis[i]->getPosition().x < -20)
				{
					listeBonus[0]->Remove_Observer(ennemis[i]);
					delete ennemis[i];
					ennemis[i] = nullptr;
				}

				//Verifier si le boss doit prendre l'ennemi
				if (this->boss != nullptr)
				{
					if (ennemis[i] != nullptr)
					{
						//Vérifie la collision avec la catching box, qui est un peu plus grande que les boss.
						if (ennemis[i]->VerifierCollisionAvecJoueur(*this->boss->GetCatchingBox()))
						{
							this->boss->AjouterEnnemi(this->ennemis[i]);
							listeBonus[0]->Remove_Observer(ennemis[i]);
							this->ennemis[i] = nullptr;
						}
						if (this->boss->getPosition().x < -200)
						{
							delete this->boss;
							this->boss = nullptr;
						}
					}
				}
			}
		}
	}

	//Mouvement et tir du boss
	if (this->boss != nullptr)
	{
		isShooting = rand() % 200;
		if (isShooting < 10)
			this->AddShot(this->boss->tirer(this->vaisseauJoueur));

		this->boss->Mouvement();
	}

	//Mouvement des tirs
	for (int i = 0; i < NB_MAX_TIRS; i++)
	{
		if (this->tirs[i] != nullptr)
		{
			//si c'est un tir charge,
			if (typeid(*this->tirs[i]) == typeid(TirCharge))
			{
				//Appel ça méthode specifique de déplacement.
				TirCharge* t = (TirCharge*)this->tirs[i];
				if (t->Move(this->vaisseauJoueur))
					this->vaisseauJoueur->SetIsCharging(true);
				//Si la bar d'espace est relâchée,
				if (!Controls::tir)
				{
					//si la charge est suffisant, effectue le tir, sinon le détruit.
					if (t->GetCharge() <= 10 && t->GetCharge() > 0)
					{
						delete t;
						this->tirs[i] = nullptr;
						this->vaisseauJoueur->SetIsCharging(false);
					}
					else
					{
						t->Shoot();
						this->vaisseauJoueur->SetIsCharging(false);
					}
				}	
			}
			else
				this->tirs[i]->Move();
			//delete le tir s'il sort de l'écran à l'exception d'un tir chargé qui est en charge.
			if (tirs[i] != nullptr)
			{
				if (this->tirs[i]->getPosition().x < 0 ||
					this->tirs[i]->getPosition().y < 0 ||
					this->tirs[i]->getPosition().x > LARGEUR ||
					this->tirs[i]->getPosition().y > HAUTEUR)
				{
					if (typeid(*this->tirs[i]) == typeid(TirCharge))
					{
						TirCharge* t = (TirCharge*)this->tirs[i];
						if (t->IsShot())
						{
							delete this->tirs[i];
							this->tirs[i] = nullptr;
						}
					}
					else
					{
						delete this->tirs[i];
						this->tirs[i] = nullptr;
					}
				}
			}
		}
	}
	// Mouvement des obstacles 
	for (int i = 0; i < NB_MAX_OBSTACLE; i++)
	{
		if (obstacles[i] != nullptr)
		{
			obstacles[i]->Move();
			if (!obstacles[i]->EstDansLeJeu())
			{
				Subject::Remove_Observer(obstacles[i]);
				delete obstacles[i];
				obstacles[i] = nullptr;
			}
		}
	}
		

}

void Game::BonusUpdate()
{
	// Gestion de la liste de bonus
	ActiverBonus(vaisseauJoueur->GetRect());
	for (int i = 0; i < MAX_NB_BONUS; i++)
	{
		if (listeBonus[i] != nullptr)
		{
			// Le bonus effectue son action
			if (listeBonus[i]->Actif())
				listeBonus[i]->Action();
			// Si on a affaire à un bouclier, sa position est mise à jour
			if (typeid(*listeBonus[i]) == typeid(Bouclier) && listeBonus[i]->Collected())
			{
				Bouclier* b = (Bouclier*)listeBonus[i];
				b->SetPosition(Vector2f(vaisseauJoueur->getPosition().x - (vaisseauJoueur->getGlobalBounds().width / 2), vaisseauJoueur->getPosition().y - (vaisseauJoueur->getGlobalBounds().height)));
			}
			// Si le bonus n'est plus utile, il est supprimé
			if (listeBonus[i]->EstTermine())
			{
				// Décrémenter le multiplicateur de point si on en supprime un
				if (typeid(*listeBonus[i]) == typeid(Multiplicateur))
					vaisseauJoueur->EnleverMultiplicateur();
				// Mettre à jour l'interface si on supprime un bouclier
				if (typeid(*listeBonus[i]) == typeid(Bouclier))
				{
					vaisseauJoueur->EnleverBouclier();
					if (vaisseauJoueur->GetPremierBouclier() == nullptr)
						UI::ResetBouclier();				
				}
				delete listeBonus[i];
				listeBonus[i] = nullptr;
			}
			//Si c'est un arme, il est stocké dans la liste du joueur et c'est elle qui va faire
			//le delete le moment venu, l'arme doit tout de même être retirée da liste des bonus.
			else if (this->listeBonus[i]->IsArme() && listeBonus[i]->Collected())
			{
				listeBonus[i] = nullptr;
			}
				
		}

 	}
}

/// <summary>
/// Dessine tous les objets du jeu à l'écran.
/// </summary>
void Game::Draw()
{
	mainWin.clear();
	//Dessine le fond.
	fond.Draw(&mainWin);
	//Dessine le joueur.
	mainWin.draw(*vaisseauJoueur);
	//Dessine les vaisseaux ennemis.
	for (int i = 0; i < NBR_VAISSEAUX; i++)
	{
		if (ennemis[i] != nullptr)
		{
			mainWin.draw(*ennemis[i]);
			//mainWin.draw(ennemis[i]->GetCollisionBox());
		}

	}

	//Dessine les tirs.
	for (int i = 0; i < NB_MAX_TIRS; i++)
	{
		if (this->tirs[i] != nullptr)
		{
			//Les type de tirs ont leur prodres méthodes draw.
			if (typeid(*this->tirs[i]) == typeid(TirEvantail))
			{
				TirEvantail* t = (TirEvantail*)this->tirs[i];
				t->Draw(this->mainWin);
			}
			else if (typeid(*this->tirs[i]) == typeid(TirBoss))
			{
				TirBoss* t = (TirBoss*)this->tirs[i];
				t->Draw(this->mainWin);
			}
			else
				mainWin.draw(*this->tirs[i]);
		}	
	}
	
	//Dessine les bonus.
	for (int i = 0; i < MAX_NB_BONUS; i++)
	{
		if (listeBonus[i] != nullptr)
		{
			if(typeid(*listeBonus[i]) == typeid(Bouclier) && listeBonus[i]->Collected())
			{
				Bouclier* b = (Bouclier*)listeBonus[i];
				mainWin.draw(b->GetShape());
			}
			else
				mainWin.draw(*listeBonus[i]);
		}
			
	}

	//Dessine les obstacles.
	for (int i = 0; i < NB_MAX_OBSTACLE; i++)
		if (obstacles[i] != nullptr)
			mainWin.draw(*obstacles[i]);

	//Dessine le boss.
	if (this->boss != nullptr)
	{
		this->boss->Draw(this->mainWin);
		this->boss->GetCollisionBox();
	}

	UI::Draw(&mainWin);

	mainWin.display();
}

/// <summary>
/// Génère un ennemis aléatoirement (peu ne pas en générer).
/// </summary>
void Game::GenererEnnemi()
{
	//Incrémente le compteur.
	compteurEnnemi++;
	//Si le compteur est égale à la valeur qu'il doit être pour générer un nouveau vaisseau,
	if (compteurEnnemi == prochainVaisseau)
	{
		//remettre le compteur à 0 et mettre une nouvelle valeur è atteindre pour le compteur.
		compteurEnnemi = 0;
		prochainVaisseau = rand() % 100 + 15;
		//Trouver le premier indice null du tableau d'ennemis,
		for (int i = 0; i < NBR_VAISSEAUX; i++)
		{
			if (ennemis[i] == nullptr)
			{
				//puis générer un type d'ennemis aléatoirement et l'ajouter à l'indice trouvé.
				int choix = rand() % 5;
				ennemis[i] = EnnemiFactory::CreerEnnemi(typesEnnemis(choix));
				ennemis[i]->InitGraphiques();
				// Un ennemi nouvellement généré doit être ajouté aux observeurs
				Subject::Add_Observer(ennemis[i]);
				break;
			}
		}
	}

	//Si le variable frames atteint 1000, générer un boss, puis remettre la variable à 0.
	if (this->frames >= 1000)
	{
		if (boss == nullptr)
		{
			this->boss = new Boss();
			this->boss->InitGraphiques();
			frames = 0;
		}
	}
}

/// <summary>
/// Génère un obstacle aléatoirement, fonctionne avec le même principe que la génération d'ennemis.
/// </summary>
void Game::GenererObstacle()
{
	compteurObstacle++;
	if (compteurObstacle == prochainObstacle)
	{
		compteurObstacle = 0; 
		prochainObstacle = rand() % 300 + 15;
		for (int i = 0; i < NB_MAX_OBSTACLE; i++)
		{
			if (obstacles[i] == nullptr)
			{
				obstacles[i] = new Obstacle();
				Subject::Add_Observer(obstacles[i]);
				break;
			}
		}
	}
}

/// <summary>
/// Active les bonus qui viennent d'être collectés par le joueur.
/// </summary>
/// <param name="rect">Rectangle du joueur qui sert à vérifier s'il rentre en contact avec le bonus.</param>
void Game::ActiverBonus(IntRect rect)
{
	for (int i = 0; i < MAX_NB_BONUS; i++)
	{
		if (listeBonus[i] != nullptr)
		{
			if (listeBonus[i]->TesterContact(rect))
			{
				SoundPlayer::PlaySound("select");
				listeBonus[i]->Activer();
				if (typeid(*listeBonus[i]) != typeid(BombeExplo))
				{
					listeBonus[i]->Collect();
				}
			}
		}
	}
}

/// <summary>
/// Met à jour les projectiles.
/// </summary>
void Game::ProjectileUpdate()
{
	// Collision des projectiles avec les entités
	for (int i = 0; i < NB_MAX_TIRS; i++)
	{
		if (tirs[i] != nullptr)
		{
			// Collision avec le joueur
			if (!tirs[i]->VientDuJoueur() && tirs[i]->VerifierCollision(vaisseauJoueur))
			{
				delete tirs[i];
				tirs[i] = nullptr;
			}
			// Collision avec les ennemis 
			else if (tirs[i] != nullptr && tirs[i]->VientDuJoueur())
			{
				for (int j = 0; j < NBR_VAISSEAUX; j++)
				{
					if (ennemis[j] != nullptr)
					{
						if (tirs[i]->VerifierCollision(ennemis[j]))
						{
							vaisseauJoueur->AjouterScore(ennemis[j]->GetPoints());
							UI::SetPoints(vaisseauJoueur->GetScore());
							if (this->tirs[i]->ToDelete())
							{
								delete tirs[i];
								tirs[i] = nullptr;
							}
							break;
						}
					}
				}

				//Collision avec le boss.
				if (boss != nullptr)
				{
					if (this->tirs[i] != nullptr)
					{
						if (this->tirs[i]->VientDuJoueur())
						{
							if (this->tirs[i]->VerifierCollision(this->boss))
							{
								if (this->tirs[i]->ToDelete())
								{
									delete tirs[i];
									tirs[i] = nullptr;
								}
							}
						}
					}
				}
			}
		}
	}

	if (this->boss != nullptr)
	{
		if (this->boss->GetPV() < 0)
		{
			GenererBonus(boss);
			delete this->boss;
			this->boss = nullptr;
		}
	}
}

/// <summary>
/// Met à jour les obstacles.
/// </summary>
void Game::ObstacleUpdate()
{
	for (int j = 0; j < NB_MAX_OBSTACLE; j++)
	{
		if (obstacles[j] != nullptr)
		{
			for (int i = 0; i < NBR_VAISSEAUX; i++)
			{
				if (ennemis[i] != nullptr)
				{
					if (obstacles[j]->VerifierCollision(ennemis[i]))
					{
						//Si l'obstacle entre en collision avec un ennemis, le détruire.
						Subject::Remove_Observer(ennemis[i]);
						GenererBonus(ennemis[i]);
						delete ennemis[i];
						ennemis[i] = nullptr;
					}
				}
			}
			//Si l'obstacle entre en collision avec le joueur, le détruit.
			if (obstacles[j]->VerifierCollision(vaisseauJoueur))
			{
				vaisseauJoueur->InfligerDegats(vaisseauJoueur->GetPV());
				break;
			}
		}
	}

}
/// <summary>
/// Génère un bonus aléatoirement.
/// </summary>
/// <param name="ennemi">L'ennemis qui ne devra pas être ajouté à la liste d'observeurs.</param>
void Game::GenererBonus(Ennemi* ennemi)
{
	// Dropper un bonus
	for (int j = 0; j < MAX_NB_BONUS; j++)
	{
		if (listeBonus[j] == nullptr)
		{
			int random = rand() % 40;
			listeBonus[j] = BonusFactory::CreerBonus(random, Vector2f(ennemi->getPosition().x + 20, ennemi->getPosition().y - (ennemi->getGlobalBounds().height) / 2));
			if (listeBonus[j] != nullptr)
			{
				listeBonus[j]->InitGraphiques();
				listeBonus[j]->Add_Observer(vaisseauJoueur);
				for (int k = 0; k < NBR_VAISSEAUX; k++)
				{
					// Ajouter en observeur tous les ennemis sauf celui qui le dépose
					if (ennemis[k] != nullptr)
					{
						listeBonus[j]->Add_Observer(ennemis[k]);
					}
				}
				listeBonus[j]->Remove_Observer(ennemi);
			}
			break;
		}

	}
}
