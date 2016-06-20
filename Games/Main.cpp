#include <Engine\Engine.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>

//Namespace
using namespace Penguin;

//Dev mode is active or not
//#define DEV_MODE

//Special text
#define ATTRIBUTION "A game made by Cameron Bell, CEO of Obtuse Studios"
#define COMP_INFO "This game was made for Ludum Dare #35 in 48 hours! (That explains alot)"
#define MESSAGES_FILE "Assets/Misc/Messages.txt"

//All Sound effects
#define SFX_VOLUME 10

enum class SFX_Types { Death, Hit, Jump, Select };

vector<int> allDeathSounds;
const string DeathFX[] =
{
	"Assets/SFX/Death_1.wav",
	"Assets/SFX/Death_3.wav",
	"Assets/SFX/Death_3.wav"
};

vector<int> allHitSounds;
const string HitFX[] =
{
	"Assets/SFX/Hit_1.wav",
	"Assets/SFX/Hit_2.wav",
	"Assets/SFX/Hit_3.wav",
	"Assets/SFX/Hit_4.wav",
	"Assets/SFX/Hit_5.wav",
	"Assets/SFX/Hit_6.wav",
	"Assets/SFX/Hit_7.wav"
};

vector<int> allJumpSounds;
const string JumpFX[] =
{
	"Assets/SFX/Jump_1.wav",
	"Assets/SFX/Jump_2.wav",
	"Assets/SFX/Jump_3.wav",
	"Assets/SFX/Jump_4.wav",
	"Assets/SFX/Jump_5.wav",
	"Assets/SFX/Jump_6.wav",
	"Assets/SFX/Jump_7.wav"
};

vector<int> allSelectSounds;
const string SelectFX[] =
{
	"Assets/SFX/Select_1.wav",
	"Assets/SFX/Select_2.wav",
	"Assets/SFX/Select_3.wav"
};

#define MUSIC_VOLUME 100
#define SONG_1 "Assets/Songs/LD_Tune.wav"

//Fonts and text
#define FONT_SIZE 36
#define TEXT_PATH "Assets/Misc/Text_Data.txt"
#define BOLD_FONT_PATH "Assets/Fonts/Raleway-Bold.ttf"
#define NORMAL_FONT_PATH "Assets/Fonts/Raleway-Regular.ttf"

//General constants
#define GAME_FPS 60

//Tile based grid
#define TILE 64

//Level properties
#define LEVEL_WIDTH 500
#define LEVEL_HEIGHT 11
#define TILESET_ROWS 5
#define TILESET_COLUMNS 4
#define LINE_SPRITE "Assets/Images/Line.png"
#define FADE_IMAGE "Assets/Images/Fade.png"
#define LEVEL_FILE "Assets/Levels/NewLevel.csv"
#define TILESET_IMAGE "Assets/Images/Tileset.png"
#define RECTANGLE_SPRITE "Assets/Images/Player.png"
#define TILESET_IMAGE_INV "Assets/Images/Tileset_Inv.png"

//Level IDs
#define TEXT_ID 3
#define FLOOR_TOP_ID 2
#define TEXT_IMG_ID 3
#define FLOOR_LEFT_ID 6
#define FLOOR_RIGHT_ID 7
#define CORNER_LEFT_ID 8
#define CORNER_RIGHT_ID 9
#define UP_ARROW_ID 10
#define RIGHT_ARROW_ID 4
#define LEFT_ARROW_ID 5
#define PLAYER_OLD_ID 1
#define TRANSITION_ID 11
#define PLAYER_SPAWN_ID 0
#define TRANSITION_END_ID 12
#define HER_SPAWN_ID 16
#define CHECKPOINT_ID 17
#define DOWN_ARROW_ID 18

//Window properties
#define CAMERA_SPEED 3
#define CAMERA_SCALE 1
#define GAME_TITLE "Vertex"
#define SCREEN_WIDTH 20 * TILE
#define SCREEN_HEIGHT 11 * TILE
#define WINDOW_ICON "Assets/Images/Triangle.png"

//Player properties
#define FRICTION 0.8
#define MOVE_SPEED 60	
#define JUMP_POWER 14
#define MAX_VELOCITY 250
#define ROTATE_SPEED_FAST 360 * 2.5
#define ROTATE_SPEED_NORMAL 400

int GRAVITY_CONSTANT = 5;

//The total number of shapes
const int TOTAL_SHAPE_ID = 7;

//The player is one of shapes
struct ObjectShape
{
	ObjectShape(string p, float r, Vector rA, Vector lA, int jB, string n)
	{
		path = p;
		rotate = r;
		rightAnchor = rA;
		leftAnchor = lA;
		JumpBy = jB;
		name = n;
	}

	string path;		//The source image of the shape
	float rotate;		//How much to rotate by (interior angle)

	Vector rightAnchor;	//The center point when going forwards
	Vector leftAnchor;	//The center point when going backwards\

	int JumpBy;
	string name;		//Just for displaying text
};

//A list of shapes
vector<ObjectShape> AllShapes;

//Player variables
bool pGrounded = false;					//Grounded of not
float pSpeed = MOVE_SPEED;				//Movement speed
int pRotateDirection = 0;				//Where to rotate to
bool pcanMoveLeft = true;				//Can move left
bool pcanMoveRight = true;				//Check right

int pCurrentShape = TOTAL_SHAPE_ID;		//The current shape (Number of sides - 3)
bool ignoreInput = false;				//To use input or not
bool preloadSprite = false;				//Reload the player sprite
bool pDeathAnimation = false;			//Play death animation

float pRotateSpeed = ROTATE_SPEED_NORMAL; //Speed of rotation

string currnetFPS = "Null";

//Game scenes
enum class Scenes
{
	Game, Game_Line, Game_Dot, You_Lose, Menu
};

Scenes GameState = Scenes::Menu;

//Animation timers
float fadeAnimTimer = 255;
float dissapearAnimTimer = 0;

float lineFadeIn = 255;
float lineFadeOut = 0;
float lineTimer = 0;

float dotFadeIn = 255;
float dotFadeOut = 0;
float dotTimer = 0;

int intoTimer = 0;
int introAlpha = 255;

bool useIntroAnimation = true;

bool introAnimation = true;
bool startGame = false;

int main(int argc, char** argv)
{
	//Seed time
	srand(time(NULL));

	//Manually populate the array
	AllShapes.emplace_back("Assets/Images/Triangle.png", 120, Vector(TILE, TILE), Vector(0, TILE), TILE, "Triangle");
	AllShapes.emplace_back("Assets/Images/Player.png", 90, Vector(TILE, TILE), Vector(0, TILE), TILE, "Square");
	AllShapes.emplace_back("Assets/Images/Pentagon.png", 72, Vector(TILE - 13, TILE), Vector(13, TILE), TILE - 13 * 2, "Pentagon");
	AllShapes.emplace_back("Assets/Images/Hexagon.png", 60, Vector(TILE - 16, TILE), Vector(16, TILE), TILE - 16 * 2, "Hexagon");
	AllShapes.emplace_back("Assets/Images/Heptagon.png", 51.4, Vector(TILE - 16, TILE), Vector(16, TILE), TILE - 16 * 2, "Heptagon");
	AllShapes.emplace_back("Assets/Images/Octogon.png", 45, Vector(TILE - 18, TILE), Vector(18, TILE), TILE - 18 * 2, "Octagon");
	AllShapes.emplace_back("Assets/Images/Nonagon.png", 40, Vector(TILE - 20, TILE), Vector(20, TILE), TILE - 20 * 2, "Nonagon");
	AllShapes.emplace_back("Assets/Images/Decagon.png", 36, Vector(TILE - 20, TILE), Vector(20, TILE), TILE - 20 * 2, "Decagon");
	AllShapes.emplace_back("Assets/Images/Circle.png", 90, Vector(TILE, TILE), Vector(0, TILE), TILE, "Cirlce");

	//Setup
	Engine Engine;
	Engine.Window.Create("Vertex", Vector(SCREEN_WIDTH, SCREEN_HEIGHT));

	//Dont show crsor and fullscreen
	Engine.Window.SetWindowIcon(WINDOW_ICON);
	//Engine.Window.setShowMouseCursor(false);
	//Engine.Window.setFullScreen();

	//For colour changes
	Rectangle Darkness;
	Darkness.Col = Colour(0, 0, 0);

	//Load tilemap image
	Sprite TilesetSprite;
	Sprite TilesetSpriteInverted;
	TilesetSprite.Load(Engine.Window.GetRenderer(), TILESET_IMAGE, true);
	TilesetSpriteInverted.Load(Engine.Window.GetRenderer(), TILESET_IMAGE_INV, true);

	//Create tilemap
	TileMap Level(LEVEL_FILE, &TilesetSprite, Vector(TILESET_ROWS, TILESET_COLUMNS), Vector(LEVEL_WIDTH, LEVEL_HEIGHT), Vector(TILE, TILE));
	
	//Get player spawn position
	vector<Tile*> AllCheckpoints = Level.GetByID(CHECKPOINT_ID);
	Tile* PlayerSpawn = Level.GetFirstByID(PLAYER_SPAWN_ID);

	int pRespawnVertexes = TOTAL_SHAPE_ID;
	Tile* PlayerRepawn = PlayerSpawn;

	Vector PlayerSpawnPoint = PlayerSpawn->Position;

	//Get floor
	map<int, Tile>* Walls = Level.GetEntireLevel();

	//Get transition and place darkness
	Tile* Transition = Level.GetFirstByID(TRANSITION_ID);
	Tile* TransitionEnd = Level.GetFirstByID(TRANSITION_END_ID);

	if (Transition != NULL && TransitionEnd != NULL)
	{
		Darkness.Scale.x = TransitionEnd->Position.x - Transition->Position.x;
		Darkness.Position.x = Transition->Position.x;
		Darkness.Scale.y = SCREEN_HEIGHT;
		Darkness.Position.y = 0;

		//Set colour modulation
		typedef std::map<int, Tile>::iterator it_type;
		for (it_type iterator = Walls->begin(); iterator != Walls->end(); iterator++)
		{
			if (iterator->second.Position.x >= Transition->Position.x)
			{
				iterator->second.tex = TilesetSpriteInverted.getRawTexture();
			}
		}
	}


	//Fades the screen
	Sprite Fade(Vector(0, 0), Vector(SCREEN_WIDTH, SCREEN_HEIGHT));
	Fade.Load(Engine.Window.GetRenderer(), FADE_IMAGE);
	//Fade.Col.Alpha = 255;
	Fade.resetColourMod(Colour(255, 255, 255, 0));

	//Get vector of text IDs
	vector<Tile*> textPositions = Level.GetByID(TEXT_ID);
	
	//Player spawn should not be visible when rendering as well as text
	PlayerSpawn->shouldDraw = false;

	//Create player and set position
	Sprite Player(PlayerSpawn->Position);
	Player.Load(Engine.Window.GetRenderer(), AllShapes[pCurrentShape].path, true);

	//Set player center to far right
	Player.center = AllShapes[pCurrentShape].rightAnchor;

	//Line sprite

	Rectangle Line(Vector(SCREEN_WIDTH / 2 - TILE / 2, SCREEN_HEIGHT / 2 - TILE / 2));
	Line.Scale.x = TILE;
	Line.Scale.y = 4;

	Rectangle BackLine(Vector(0, SCREEN_HEIGHT / 2 - TILE / 2));
	BackLine.Col = Colour(200, 200, 200);
	BackLine.Scale.x = SCREEN_WIDTH;
	BackLine.Scale.y = 4;

	Text instructions;
	instructions.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, "Press space to continue...", 36);
	instructions.Position.x = SCREEN_WIDTH / 2 - instructions.Scale.x / 2;
	instructions.Position.y = SCREEN_HEIGHT - 100;
	instructions.center = Vector(instructions.Scale.x / 2, instructions.Scale.y / 2);
	
	Text DotMessage(Vector(0, 100));

	Rectangle Dot(Vector(SCREEN_WIDTH / 2 - 2, SCREEN_HEIGHT / 2 - 2), Vector(4, 4));
	DotMessage.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, "You are 0 dimensional, You are gone.", FONT_SIZE, SCREEN_WIDTH);;
	DotMessage.Position.x += SCREEN_WIDTH / 2 - DotMessage.Scale.x / 2;

	Text LineMessage(Vector(0, 100));
	LineMessage.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, "You are 1 dimensional, she is gone. You will be gone.", FONT_SIZE, SCREEN_WIDTH);;
	LineMessage.Position.x += SCREEN_WIDTH / 2 - LineMessage.Scale.x / 2;

	//An array of text objects
	vector<Text> textObjects;

	SpriteSheet IntroAnimation;
	useIntroAnimation = IntroAnimation.Load(Engine.Window.GetRenderer(), "Assets/Images/Animation.png", 8, 1, true);
	
	if (useIntroAnimation) IntroAnimation.Scale /= Vector(1.5, 1.5);

	Sprite IntroFrame;
	IntroFrame.Load(Engine.Window.GetRenderer(), "Assets/Images/Logo.png", true);
	IntroFrame.Scale /= Vector(1.5, 1.5);

	//Set positions
	for (int i = 0; i < textPositions.size(); i++)
	{
		//Set position
		Text temp(textPositions[i]->Position);
		textObjects.push_back(temp);
	}

	//Open text file
	fstream textData(TEXT_PATH);

	//Read in
	if (textData.good())
	{
		//Store current line
		string line = "";
		int currentLine = -1;

		while (getline(textData, line))
		{
			//Increment
			currentLine++;

			//Check
			if (currentLine < textObjects.size())
			{
				if (Transition != NULL)
				{
					if (textObjects[currentLine].Position.x >= Transition->Position.x)
					{
						textObjects[currentLine].Col = Colour(255, 255, 255);
					}
				}

				textObjects[currentLine].Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, line, FONT_SIZE);
			}

			//Throw warning
			else Debug::Warning("Too many text objects, only some used!");
		}
	}

	else Engine.Debug.Fatal("Could not text data file");

	//Dev mode text
#ifdef DEV_MODE
	Text stats(Vector(50, SCREEN_HEIGHT - 100));
	stats.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, "Undefined", 15, SCREEN_WIDTH);
#endif

	
	//Load all the sounds
	for (int i = 0; i < sizeof(HitFX) / sizeof(HitFX[0]); i++) allHitSounds.push_back(Engine.Sound.LoadSoundEffect(HitFX[i]));
	for (int i = 0; i < sizeof(JumpFX) / sizeof(JumpFX[0]); i++) allJumpSounds.push_back(Engine.Sound.LoadSoundEffect(JumpFX[i]));
	for (int i = 0; i < sizeof(DeathFX) / sizeof(DeathFX[0]); i++) allDeathSounds.push_back(Engine.Sound.LoadSoundEffect(DeathFX[i]));
	for (int i = 0; i < sizeof(SelectFX) / sizeof(SelectFX[0]); i++) allSelectSounds.push_back(Engine.Sound.LoadSoundEffect(SelectFX[i]));

	int num = Engine.Sound.AddSong(SONG_1);
	Engine.Sound.PlaySong(num, true);

	ifstream messagesFile(MESSAGES_FILE);
	vector<string> possibleMessages;

	//Load messages file
	if (messagesFile.good())
	{
		string line = "";
		
		while (getline(messagesFile, line))	possibleMessages.push_back(line);
	}

	string choosenMessage = possibleMessages[int(rand() % possibleMessages.size())];

	//All the text on the game over screen
	Text Title(Vector(0, 100));
	Text SubTitle(Vector(0, 200));
	Text Developer(Vector(0, 600));
	Text LudumDare(Vector(0, 630));
	
	Button PlayAgain(&Engine.Window, Vector(0, 450), Vector(150, 50), "Play again", NORMAL_FONT_PATH);
	Button Close(&Engine.Window, Vector(0, 525), Vector(150, 50), "Quit", NORMAL_FONT_PATH);

	Title.Load(Engine.Window.GetRenderer(), BOLD_FONT_PATH, "YOU HAVE FAILED!", 100, SCREEN_WIDTH);
	LudumDare.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, COMP_INFO, 24, SCREEN_WIDTH);
	Developer.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, ATTRIBUTION, 24, SCREEN_WIDTH);
	SubTitle.Load(Engine.Window.GetRenderer(), NORMAL_FONT_PATH, choosenMessage, 36, SCREEN_WIDTH);

	Sprite LooseAnimation(Vector(0, 325));
	LooseAnimation.Load(Engine.Window.GetRenderer(), RECTANGLE_SPRITE, true);
	LooseAnimation.center = Vector(TILE / 2, TILE / 2);

	//Center
	Title.Position.x = (SCREEN_WIDTH / 2) - (Title.Scale.x / 2);
	SubTitle.Position.x = (SCREEN_WIDTH / 2) - (SubTitle.Scale.x / 2);
	LudumDare.Position.x = (SCREEN_WIDTH / 2) - (LudumDare.Scale.x / 2);
	Developer.Position.x = (SCREEN_WIDTH / 2) - (Developer.Scale.x / 2);
	LooseAnimation.Position.x = (SCREEN_WIDTH / 2) - (LooseAnimation.Scale.x / 2);
	PlayAgain.setPosition(Vector((SCREEN_WIDTH / 2) - (PlayAgain.scale.x / 2), PlayAgain.position.y));
	Close.setPosition(Vector((SCREEN_WIDTH / 2) - (Close.scale.x / 2), Close.position.y));

	//Finally set weather tiles should be drawn or collided with
	typedef std::map<int, Tile>::iterator it_type;
	for (it_type iterator = Walls->begin(); iterator != Walls->end(); iterator++)
	{
		if (iterator->second.ID == PLAYER_SPAWN_ID){ iterator->second.shouldDraw = false; iterator->second.shouldCollide = false; }
		if (iterator->second.ID == TEXT_IMG_ID){ iterator->second.shouldDraw = false; iterator->second.shouldCollide = false; }
		if (iterator->second.ID == RIGHT_ARROW_ID){ iterator->second.shouldCollide = false; }
		if (iterator->second.ID == LEFT_ARROW_ID){ iterator->second.shouldCollide = false; }
		if (iterator->second.ID == UP_ARROW_ID){ iterator->second.shouldCollide = false; }
		if (iterator->second.ID == TRANSITION_ID){ iterator->second.shouldDraw = false; iterator->second.shouldCollide = false; }
		if (iterator->second.ID == TRANSITION_END_ID){ iterator->second.shouldDraw = false; iterator->second.shouldCollide = false; }
		if (iterator->second.ID == CHECKPOINT_ID){ iterator->second.shouldDraw = false; iterator->second.shouldCollide = false; }
		if (iterator->second.ID == DOWN_ARROW_ID){ iterator->second.shouldCollide = false; }
		if (iterator->second.ID == HER_SPAWN_ID){  iterator->second.shouldCollide = false; }
	}

	//Setup the camera
	Engine.Window.Camera.Init(Vector(SCREEN_WIDTH, SCREEN_HEIGHT), CAMERA_SCALE, Vector(LEVEL_WIDTH * TILE, LEVEL_HEIGHT * TILE));

	//Main game loop
	while (Engine.Window.GetWindowState())
	{
		//Begin
		Engine.FPS.Start();
		Engine.Window.Clear();
		Engine.Input.Check(&Engine.Window);

		//Check current scene
		if (GameState == Scenes::Game)
		{
			//Check if player sprite should be redrawn
			if (preloadSprite)
			{
				Player.Load(Engine.Window.GetRenderer(), AllShapes[pCurrentShape].path, true);
				preloadSprite = false;
			}

			//Check that player is grounded
			if (pGrounded)
			{
				if (Engine.Input.ButtonHeld(Engine.Key.UP) && !ignoreInput)
				{
					//Make player jump
					Player.Velocity.y = -JUMP_POWER;
					pGrounded = false;

					//Change shape
					if (pCurrentShape > 0)
					{
						//Play SFX
						Engine.Sound.PlaySFX(allHitSounds[int(rand() % allHitSounds.size())], SFX_VOLUME);

						pCurrentShape--;
						preloadSprite = true;
					}

					//Okay has died
					else
					{
						//Death sound
						Engine.Sound.PlaySFX(allDeathSounds[int(rand() % allDeathSounds.size())], SFX_VOLUME);

						pDeathAnimation = true;
					}
				}
			}

			//Check for sprint
			if (Engine.Input.ButtonHeld(Engine.Key.DOWN) && !pGrounded && !ignoreInput)
			{
				Player.Velocity.y += GRAVITY_CONSTANT * Engine.FPS.deltaTime * 3;
				pRotateSpeed - ROTATE_SPEED_FAST;
			}

			else if (Engine.Input.ButtonHeld(Engine.Key.DOWN)) pRotateSpeed = ROTATE_SPEED_FAST;
			else pRotateSpeed = ROTATE_SPEED_NORMAL;

			//Check for moving left
			if (Engine.Input.ButtonHeld(Engine.Key.LEFT) && pRotateDirection == 0 && !ignoreInput && pcanMoveLeft)
			{
				//Player.Velocity.x -= pSpeed * Engine.FPS.deltaTime;
				pRotateDirection = -1;
				Player.center = AllShapes[pCurrentShape].leftAnchor;
			}

			//Check for moving right
			if (Engine.Input.ButtonHeld(Engine.Key.RIGHT) && pRotateDirection == 0 && !ignoreInput && pcanMoveRight)
			{
				//Player.Velocity.x += pSpeed * Engine.FPS.deltaTime;
				pRotateDirection = 1;
				Player.center = AllShapes[pCurrentShape].rightAnchor;
			}

			//Ignore double input
			if (Engine.Input.ButtonHeld(Engine.Key.RIGHT) && Engine.Input.ButtonHeld(Engine.Key.LEFT))
				ignoreInput = true;
			else ignoreInput = false;

			//Rotate the player
			if (pRotateDirection != 0 && !pDeathAnimation)
			{
				//Increment rotation
				Player.rotation += Engine.FPS.deltaTime * pRotateSpeed * pRotateDirection;

				//Check if done to the right
				if (pRotateDirection >= 1)
				{
					if (ceil(Player.rotation) >= AllShapes[pCurrentShape].rotate)
					{
						//Reset
						Player.center = AllShapes[pCurrentShape].rightAnchor;
						Player.Position += AllShapes[pCurrentShape].JumpBy;
						Player.Scale.x;
						Player.rotation = 0;
						pRotateDirection = 0;
					}
				}

				//Check if done to the left
				else
				{
					if (ceil(Player.rotation) <= -AllShapes[pCurrentShape].rotate)
					{
						//Reset
						Player.center = AllShapes[pCurrentShape].leftAnchor;
						Player.Position.x -= AllShapes[pCurrentShape].JumpBy;
						Player.rotation = 0;
						pRotateDirection = 0;
					}
				}
			}


			//Apply friction and gravity
			Player.Velocity.x *= FRICTION;
			Player.Velocity.y += (GRAVITY_CONSTANT * GRAVITY_CONSTANT) * Engine.FPS.deltaTime;

			//Check velocity is not too high
			if (Player.Velocity.x > MAX_VELOCITY) Player.Velocity.x = MAX_VELOCITY;
			if (Player.Velocity.x < -MAX_VELOCITY) Player.Velocity.x = -MAX_VELOCITY;
			if (Player.Velocity.y > MAX_VELOCITY) Player.Velocity.y = MAX_VELOCITY;
			if (Player.Velocity.y < -MAX_VELOCITY) Player.Velocity.y = -MAX_VELOCITY;

			//Apply velocity to position
			Player.Position.x += Player.Velocity.x * Engine.FPS.deltaTime * 100;
			Player.Position.y += Player.Velocity.y * Engine.FPS.deltaTime * 100;

			//For finding deltatime
			Engine.FPS.EndMovement();

			//Can move normally
			pcanMoveLeft = true;
			pcanMoveRight = true;

			//Loop through all walls for collision
			typedef std::map<int, Tile>::iterator it_type;
			for (it_type iterator = Walls->begin(); iterator != Walls->end(); iterator++)
			{
				//Check that collision object is the floor
				if (iterator->second.ID != PLAYER_SPAWN_ID && iterator->second.shouldCollide)
				{
					//Rectangle for colliding
					Rectangle temp(Player.Position, Player.Scale);
					temp.Position.x += Player.rotation / (120 / Player.Scale.x);
					temp.rotation = Player.rotation;

#ifdef DEV_MODE
					temp.DrawOutline(&Engine.Window);
#endif

					//Check for collsion
					Manifold collisionData = Engine.Physics.CheckCollision(temp, iterator->second);

					//Resolve
					Engine.Physics.ResolveCollision(&collisionData, Player);

					//Check for collision bellow the player
					if (collisionData.Dir == Direction::Down) pGrounded = true;

					//Check differently
					Rectangle inputCheck(Player.Position, Player.Scale);
					inputCheck.Scale.x += 16;
					inputCheck.Position.x -= 8;

					Manifold inputCheckData = Engine.Physics.CheckCollision(inputCheck, iterator->second);

					if (inputCheckData.Dir == Direction::Right) { pcanMoveRight = false; }
					if (inputCheckData.Dir == Direction::Left) { pcanMoveLeft = false; }

					//Occlusion culling
					if (iterator->second.Position.x > Engine.Window.Camera.position.x + SCREEN_WIDTH)
						iterator->second.shouldDraw = false;

					else if (iterator->second.Position.x + TILE < Engine.Window.Camera.position.x)
						iterator->second.shouldDraw = false;

					else iterator->second.shouldDraw = true;
				}

			}

			//Check for passing checkpoint
			for (int i = 0; i < AllCheckpoints.size(); i++)
			{
				if (Player.Position.x >= AllCheckpoints[i]->Position.x)
				{
					PlayerRepawn = AllCheckpoints[i];
					pRespawnVertexes = pCurrentShape;
					AllCheckpoints.erase(AllCheckpoints.begin() + i);
				}
			}

			//Check for death
			if (Player.Position.y >= SCREEN_HEIGHT) 
			{
				Player.Position = PlayerRepawn->Position;
				Player.Velocity = Vector(0, 0);
				Player.rotation = 0;
				pCurrentShape = pRespawnVertexes;
				Player.Velocity = Vector(0, 0);
				Player.rotation = 0;
				GRAVITY_CONSTANT = 5;
				pDeathAnimation = false;
				preloadSprite = true;
				ignoreInput = false;
				fadeAnimTimer = 255;

				//Anim vars
				lineFadeIn = 255;
				lineFadeOut = 0;
				lineTimer = 0;

				dotFadeIn = 255;
				dotFadeOut = 0;
				dotTimer = 0;

				Fade.resetColourMod(Colour(255, 255, 255, 0));
			}

			//Follow the player
			if (!ignoreInput)
			{
				Engine.Window.Camera.Follow(Vector(Player.Position.x + SCREEN_WIDTH / 4, Player.Position.y), Engine.FPS.deltaTime * CAMERA_SPEED);
			}

			//Draw darkness bellow everything
			Darkness.Draw(&Engine.Window);

			//Draw the text
			for (int i = 0; i < textObjects.size(); i++)
			{
				//Change text if required
				string line(textObjects[i].getText());

				if (line.find("$") != string::npos) line.replace(line.find("$"), 1, to_string(pCurrentShape));
				if (line.find("#") != string::npos) line.replace(line.find("#"), 1, AllShapes[pCurrentShape].name);

				bool changed= textObjects[i].getText() != line;

				if (changed)
				{
					textObjects[i].SetText(Engine.Window.GetRenderer(), line);
					textObjects[i].Draw(&Engine.Window);

					if (line.find(to_string(pCurrentShape)) != string::npos) line.replace(line.find(to_string(pCurrentShape)), to_string(pCurrentShape).length(), "$");
					if (line.find(AllShapes[pCurrentShape].name) != string::npos) line.replace(line.find(AllShapes[pCurrentShape].name), AllShapes[pCurrentShape].name.length(), "#");

					if (textObjects[i].getText() != line)
					{
						textObjects[i].SetText(Engine.Window.GetRenderer(), line);
					}
				}
			}

			//Play death animation
			if (pDeathAnimation)
			{
				GRAVITY_CONSTANT = 0;
				Player.Velocity.y *= 0.8f;
				ignoreInput = true;

				dissapearAnimTimer += 3.5f;
				Colour Fadetemp = Fade.Col;
				Fadetemp.Alpha = dissapearAnimTimer;

				Engine.Window.Camera.Follow(Player.Position - SCREEN_WIDTH / 2, Engine.FPS.deltaTime * 10);

				
				if (dissapearAnimTimer >= 255 && AllCheckpoints.size() == 0)
				{
					//Movement
					Player.center = Vector(TILE / 2 - ((Player.rotation) * Engine.FPS.deltaTime), TILE / 2);
					Player.rotation += Engine.FPS.deltaTime * (Player.rotation + 1) * 3;

					Fadetemp.Alpha = 255;

					if (fadeAnimTimer <= 0)
					{
						Fade.resetColourMod(Colour(255, 255, 255, 0));
						pDeathAnimation = false;
						GameState = Scenes::Game_Line;
					}

					fadeAnimTimer -= 1;

					Colour temp = Player.Col;
					temp.Alpha = fadeAnimTimer;
					Player.resetColourMod(temp);
				}
				else if (dissapearAnimTimer >= 255)
				{
					Fadetemp.Alpha = 255;

					if (fadeAnimTimer <= 0)
					{
						pDeathAnimation = false;
						GameState = Scenes::You_Lose;
					}
				
					fadeAnimTimer -= 3;
					Colour temp = Player.Col;
					temp.Alpha = fadeAnimTimer;
					Player.resetColourMod(temp);
				}

				Fade.resetColourMod(Fadetemp);
			}

			//Draw everything
			Level.Draw(&Engine.Window);

			//This line of code is pathetic
			//It is a lazy solution for a problem that could have been fixed properly.
			//But it LD and I mean hey, Wo cares?
			Rectangle fix(Vector(0, 0), Vector(TILE * 2, TILE * 2), Colour(255, 255, 255));
			fix.Draw(&Engine.Window);

			//Draw fade plane
			Fade.Draw(&Engine.Window, true);

			//Depending on state draw player
			Player.Draw(&Engine.Window);

			//Draw dev mode text
#ifdef DEV_MODE
			//Set
			stats.SetText(Engine.Window.GetRenderer(), "Player position: " + to_string(Player.Position.x)
				+ "x" + to_string(Player.Position.y) + "                                         " +
				"Player rotation: " + to_string(Player.rotation) +
				+"\n" + "Player grounded: " + to_string(pGrounded) + "                                                                            " +
				AllShapes[pCurrentShape].name + "\n" +
				+"Can move left: " + to_string(pcanMoveLeft) +  +
				"Can move right: " + to_string(pcanMoveRight) + "\nDelta time: " + to_string(Engine.FPS.deltaTime) + "\n" +
				currnetFPS, SCREEN_WIDTH);

			//Draw
			stats.Draw(&Engine.Window, true);

#endif
		}
		else if (GameState == Scenes::Menu)
		{
			//Play intro animation
			if (introAnimation)
			{
				intoTimer++;
				if (int(intoTimer / 50) % 2 == 0) instructions.rotation = 3;
				else instructions.rotation = -3;

				if (Engine.Input.ButtonDown(Engine.Key.SPACE)) startGame = true;

				if (startGame)
				{
					introAlpha -= 10;
					ignoreInput = true;

					if (useIntroAnimation)
						IntroAnimation.resetColourMod(Colour(255, 255, 255, introAlpha));

					if (introAlpha <= 0)
					{
						if (useIntroAnimation)
							IntroAnimation.resetColourMod(Colour(255, 255, 255, 0));
						ignoreInput = false;
						introAnimation = false;
						GameState = Scenes::Game;
					}
				}
			}
			if (useIntroAnimation) IntroAnimation.Draw(&Engine.Window, true);
			else IntroFrame.Draw(&Engine.Window, true);
			instructions.Draw(&Engine.Window, true);
		}

		else if (GameState == Scenes::You_Lose)
		{
			//Rotate
			LooseAnimation.rotation += 1;


			if (PlayAgain.pressed()) 
			{
				Player.Velocity = Vector(0, 0);
				Player.rotation = 0;
				fadeAnimTimer = 255;
				pCurrentShape = TOTAL_SHAPE_ID;
				GRAVITY_CONSTANT = 5;
				pRespawnVertexes = TOTAL_SHAPE_ID;
				ignoreInput = false;
				pDeathAnimation = false;
				preloadSprite = true;

				//Anim vars
				lineFadeIn = 255;
				lineFadeOut = 0;
				lineTimer = 0;

				dotFadeIn = 255;
				dotFadeOut = 0;
				dotTimer = 0;

				Fade.resetColourMod(Colour(255, 255, 255, 0));

				Player.Position = PlayerSpawn->Position;
				PlayerRepawn = PlayerSpawn;

				//Get player spawn position
				AllCheckpoints = Level.GetByID(CHECKPOINT_ID);
				PlayerSpawn = Level.GetFirstByID(PLAYER_SPAWN_ID);

				GameState = Scenes::Game;
			}

			if (Close.pressed()) Engine.Window.Quit();

			//Draw button
			Close.Draw(&Engine.Window, &Engine.Input);
			PlayAgain.Draw(&Engine.Window, &Engine.Input);

			//Draw text
			LooseAnimation.Draw(&Engine.Window, true);
			Developer.Draw(&Engine.Window, true);
			LudumDare.Draw(&Engine.Window, true);
			SubTitle.Draw(&Engine.Window, true);
			Title.Draw(&Engine.Window, true);
		}
		else if (GameState == Scenes::Game_Line)
		{
			if (Engine.Input.ButtonHeld(Engine.Key.LEFT) && Line.Position.x > 0) Line.Velocity.x = -MOVE_SPEED / 8;
			if (Engine.Input.ButtonHeld(Engine.Key.RIGHT) && Line.Position.x < SCREEN_WIDTH - TILE) Line.Velocity.x = MOVE_SPEED / 8;

			Line.Velocity.x *= FRICTION;

			Line.Position.x += Line.Velocity.x;

			lineFadeIn -= 10;
			int resultAlpha = lineFadeIn;

			if (lineFadeIn <= 0)
			{
				lineFadeIn = 0;

				lineTimer += 1;

				resultAlpha = lineFadeIn;

				if (lineTimer >= 300)
				{
					lineFadeOut += 10;

					resultAlpha = lineFadeOut;

					if (lineFadeOut >= 255) GameState = Scenes::Game_Dot;
				}
			}


			Fade.resetColourMod(Colour(255, 255, 255, 0));
			
			BackLine.Draw(&Engine.Window, true);
			Line.Draw(&Engine.Window, true);
			LineMessage.Draw(&Engine.Window, true);
			Fade.Draw(&Engine.Window, true);
		}
		else if (GameState == Scenes::Game_Dot)
		{
			dotFadeIn -= 10;
			int resultAlpha = dotFadeIn;

			if (dotFadeIn <= 0)
			{
				dotFadeIn = 0;

				dotTimer += 1;

				resultAlpha = dotFadeIn;

				if (dotTimer >= 300)
				{
					dotFadeOut += 10;

					resultAlpha = dotFadeOut;

					if (dotFadeOut >= 255) GameState = Scenes::You_Lose;
				}
			}


			Fade.resetColourMod(Colour(255, 255, 255, resultAlpha));

			DotMessage.Draw(&Engine.Window, true);
			Dot.Draw(&Engine.Window, true);
			Fade.Draw(&Engine.Window, true);
		}
		
		//Stop
		Engine.Window.Draw();
		currnetFPS = Engine.FPS.Update(1000 / GAME_FPS);
	}

	//Close off
	Engine.Window.Quit();
	return 0;
}