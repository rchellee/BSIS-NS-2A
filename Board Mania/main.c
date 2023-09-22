#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "pthread.h"
#include <stdatomic.h>
#include <time.h>
#define NUM_FRAMES 3
#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
// Define the 4 basic GameBoy green colors
#define GB_GREEN01 \
    (Color) { 155, 188, 15, 255 }
#define GB_GREEN02 \
    (Color) { 110, 150, 27, 255 }
#define GB_GREEN03 \
    (Color) { 48, 98, 48, 255 }
#define GB_GREEN04 \
    (Color) { 15, 56, 15, 255 }
#define MAX_INPUT_CHARS 1
// Enums and struct data types
//----------------------------------------------------------------------------------
static float timePlayed1 = 0.0f;
static bool pause1 = false;
static char p1Ans[MAX_INPUT_CHARS + 1] = "\0";
static char p2Ans[MAX_INPUT_CHARS + 1] = "\0";
static int p2letterCount = 0, letterCount = 0, framesCounter = 0, player = 1;
static Rectangle textBox = {750, 450, 180, 50};
static bool mouseOnText = false;
static Rectangle p2textBox = {480, 450, 180, 50};
static bool damouseOnText = false;
static int p2framesCounter = 0;
typedef enum
{
    GAMEPLAY,
    CREDITS,
    ENDING
} GameScreen;
static const int screenWidth = 1166;
static const int screenHeight = 690;
static int currentScreen = GAMEPLAY;
static int elementPositionY = -128;
static int scrollingY = 0;
static int optionSelect = 0; // Main menu option selection
static float creditsScrollingPosY = (float)screenHeight + 20.0f;
static bool showInGameMenu = false;
static int endingResult = 0; // 0-Lose, 1-Win
static Sound fxMenuMove = {0};
static Sound fxMenuSelect = {0};
static Sound fxPause = {0};
static Sound fxEnding = {0};
static Sound fxLogo = {0};
static Music musicTitle = {0};
static Font font = {0};
static Texture2D Logo = {0};
static Sound fxButton = {0};
static Music music2 = {0};
static Vector2 position1 = {300.0f, 310.0f};
static Rectangle frameRec1 = {0};
static int currentFrame1 = 0;
static int framesCounter1 = 0;
static int framesSpeed1 = 1;
static Texture2D board = {0};
static int p1 = 0, p2 = 0;
static Texture2D texLogo = {0};
static Texture2D texture1 = {0};
static Texture2D texture2 = {0};
static Texture2D texture3 = {0};
static Texture2D texture4 = {0};
static Texture2D texture5 = {0};
static Texture2D texture6 = {0};
static Texture2D texture7 = {0};
static Texture2D texture8 = {0};
static Texture2D texture9 = {0};
static Texture2D texture10 = {0};
static Texture2D texture11 = {0};
static Texture2D texture12 = {0};
static Texture2D texture13 = {0};
static Texture2D texture14 = {0};
static Texture2D texture15 = {0};
static Texture2D texture17 = {0};
static Texture2D texture16 = {0};
static Texture2D texture18 = {0};
static Texture2D texture19 = {0};
static Texture2D texture20 = {0};
static Texture2D texture21 = {0};

static Texture2D texture22 = {0};
static Texture2D texture23 = {0};
static Texture2D texture24 = {0};
static Texture2D texture25 = {0};
static Texture2D texture26 = {0};
static Texture2D texture27 = {0};
static Texture2D texture28 = {0};
static Texture2D texture29 = {0};
static Texture2D texture30 = {0};
static Texture2D texture31 = {0};
static Texture2D texture32 = {0};
static Texture2D texture33 = {0};
static Texture2D texture34 = {0};
static Texture2D texture35 = {0};
static Texture2D texture36 = {0};
static Texture2D texture37 = {0};
static Texture2D texture38 = {0};
static Texture2D texture39 = {0};
static Texture2D texture40 = {0};
static Texture2D texture41 = {0};
static Texture2D texture42 = {0};
static Texture2D dice1 = {0};
static Texture2D dice2 = {0};
static Texture2D dice3 = {0};
static Texture2D retro = {0};
static int p1ques = 0;
static int p2ques = 0;
static int dice = 0;
static int p2Prev = 0;
static int p1Prev = 0;

// Module Functions Declaration (local)
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void); // Update and Draw one frame

static atomic_bool dataLoaded = ATOMIC_VAR_INIT(false);
static void *LoadDataThread(void *arg);
static bool exitGame = false;
static Texture2D texTitleLogo = {0};

static int dataProgress = 0;
static void *LoadDataThread(void *arg)
{
    int timeCounter = 0;
    clock_t prevTime = clock();

    while (timeCounter < 5000)
    {
        clock_t currentTime = clock() - prevTime;
        timeCounter = currentTime * 1000 / CLOCKS_PER_SEC;

        dataProgress = timeCounter / 10;
    }

    atomic_store(&dataLoaded, true);

    return NULL;
}

int lobby()
{
    const int screenW = 800;
    const int screenH = 450;

    InitWindow(screenW, screenH, "BOARD MANIA");

    InitAudioDevice();
    fxLogo = LoadSound("resources/logo.wav");
    Sound fxButton = LoadSound("resources/buttonfx.wav");   // Load button sound
    Texture2D button = LoadTexture("resources/button.png"); // Load button texture
    float frameHeight = (float)button.height / NUM_FRAMES;
    Rectangle sourceRec = {0, 0, (float)button.width, frameHeight};
    // Define button bounds on screen
    Rectangle btnBounds = {screenWidth / 3.0f - button.width / 2.0f, screenHeight / 1.5f - button.height / NUM_FRAMES / 0.7f, (float)button.width, frameHeight};
    int btnState = 0;       // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false; // Button action should be activated
    Vector2 mousePoint = {0.0f, 0.0f};

    Texture2D background = LoadTexture("resources/cyberpunk_street_background.png");
    Vector2 bg = {200.0f, 370.0f};
    float scrollingBack = 0.0f;

    Sound musicL = LoadSound("resources/SquidGame.wav");
    Music musicGameplay = LoadMusicStream("resources/music_title.mp3");
    PlayMusicStream(musicGameplay);

    texTitleLogo = LoadTexture("resources/title_raylib_logo.png");
    texLogo = LoadTexture("resources/logo.png");
    Texture2D Logo = LoadTexture("resources/Title.png");

    pthread_t threadId;

    enum
    {
        STATE_WAITING,
        STATE_LOADING,
        STATE_FINISHED
    } state = STATE_WAITING;
    int framesCounter = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose() && !exitGame)
    {
        mousePoint = GetMousePosition();
        btnAction = false;
        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                btnState = 2;
            else
                btnState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                btnAction = true;
                exitGame = true;
            }
        }
        else
            btnState = 0;

        if (btnAction)
        {
            PlaySound(fxButton);
        }
        sourceRec.y = btnState * frameHeight;
        framesCounter++;

        elementPositionY++;
        if (elementPositionY == (screenH / 2 - 64 - 1))
        {
            PlaySound(fxLogo);
            PlayMusicStream(musicTitle);
        }
        if (elementPositionY > (screenH / 2 - 64))
            elementPositionY = screenH / 2 - 64;
        if (framesCounter > 300)
        {
            framesCounter = 0;
        }
        UpdateMusicStream(musicGameplay);
        if (IsKeyPressed(KEY_SPACE))
        {
            StopMusicStream(musicGameplay);
        }
        scrollingBack -= 0.1f;

        if (scrollingBack <= -background.width)
            scrollingBack = 0; // -0.1f<=

        switch (state)
        {
        case STATE_WAITING:
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                int error = pthread_create(&threadId, NULL, &LoadDataThread, NULL);
                if (error != 0)
                    TraceLog(LOG_ERROR, "Error creating loading thread");
                else
                    TraceLog(LOG_INFO, "Loading thread initialized successfully");
                PlaySound(musicL);
                state = STATE_LOADING;
            }
        }
        break;
        case STATE_LOADING:
        {
            framesCounter++;
            if (atomic_load(&dataLoaded))
            {
                framesCounter = 0;
                state = STATE_FINISHED;
                StopMusicStream(musicGameplay);
            }
        }
        break;
        default:
            break;
        }
        BeginDrawing();

        ClearBackground(GetColor(0x052c46ff));

        DrawTextureEx(background, (Vector2){scrollingBack, 20}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){background.width * 55 + scrollingBack, 20}, 0.0f, 2.0f, WHITE);
        DrawText("BOARD MANIA", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        DrawTexture(Logo, screenW / 2 - 200, elementPositionY, WHITE);
        switch (state)
        {
        case STATE_WAITING:
            DrawText("PRESS SPACE to START LOADING THE GAME", 150, 400, 20, MAGENTA);
            break;
        case STATE_LOADING:
        {
            DrawRectangle(150, 330, dataProgress, 60, BLACK);
            if ((framesCounter / 15) % 2)
                DrawText("GAME LOADING...", 250, 340, 40, MAGENTA);
            DrawRectangleLines(150, 330, 500, 60, BLACK);
        }
        break;
        case STATE_FINISHED:
        {
            DrawRectangle(150, 330, 500, 60, DARKGRAY);
            DrawText("GAME LOADED!", 250, 340, 40, BLACK);
            DrawTexture(texTitleLogo, 780 - texTitleLogo.width + 5, 450 - texTitleLogo.height + 3, WHITE);
            DrawRectangleLines(150, 330, 500, 60, BLACK);
            DrawTextureRec(button, sourceRec, (Vector2){btnBounds.x, btnBounds.y}, WHITE); // Draw button frame
        }
        break;
        default:
            break;
        }
        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(texLogo);
    UnloadTexture(Logo);
    UnloadTexture(button);
    UnloadSound(fxButton);
    UnloadSound(musicL);
    CloseAudioDevice();
    CloseWindow();
}
int instructions()
{
    InitWindow(screenWidth, screenHeight, "BOARD MANIA");

    InitAudioDevice();

    Music music = LoadMusicStream("resources/country.mp3");

    PlayMusicStream(music);

    float timePlayed = 0.0f;
    bool pause = false;

    Texture2D dice = LoadTexture("resources/dice.png");
    Vector2 position = {600.0f, 470.0f};
    Rectangle frameRec = {0.0f, 0.0f, (float)dice.width / 6, (float)dice.height};

    int currentFrame = 0, framesCount = 0, framesSpeed = 8, addFramesCounter = 0;

    Texture2D instruction = LoadTexture("resources/instructions.png");

    const char message[300] = "Welcome, esteemed player, to board mania. \n The board game where luck lacks and \nknowledge is abundant.\nThe rules are simple:\nRoll the dice.\nAnswer a question.\nGet it right, proceed to the tile.\nGet it wrong, stay and wait.\nFirst to reach the end begins their victory.\n- Board Mania Creators";

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        addFramesCounter++;

        framesCount++;

        if (framesCount >= (60 / framesSpeed))
        {
            framesCount = 0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;

            frameRec.x = (float)currentFrame * (float)dice.width / 6;
        }

        UpdateMusicStream(music);
        timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) * 400;

        if (timePlayed > 400)
            StopMusicStream(music);

        BeginDrawing();

        ClearBackground(BLANK);

        DrawTexture(instruction, 2, 0, RAYWHITE);
        Texture2D P1 = LoadTexture("resources/P1.png");
        Texture2D P2 = LoadTexture("resources/P2.png");
        DrawTextureRec(dice, frameRec, position, WHITE); // Draw part of the texture
        DrawText(TextSubtext(message, 0, addFramesCounter / 10), 200, 190, 25, BLACK);
        DrawText("BOARD MANIA", screenWidth - 300, screenHeight - 20, 10, RAYWHITE);
        DrawText("Press ESC to START THE GAME", 350, 670, 20, MAGENTA);

        EndDrawing();
    }

    UnloadTexture(instruction);
    UnloadTexture(dice);

    CloseAudioDevice();
}
int maingame()
{

    // Text Font loading
    font = LoadFont("resources/alpha_beta.png");
    board = LoadTexture("resources/BoardGame.png");
    texture1 = LoadTexture("resources/player1/1.png");
    texture2 = LoadTexture("resources/player1/2.png");
    texture3 = LoadTexture("resources/player1/3.png");
    texture4 = LoadTexture("resources/player1/4.png");
    texture5 = LoadTexture("resources/player1/5.png");
    texture6 = LoadTexture("resources/player1/6.png");
    texture7 = LoadTexture("resources/player1/7.png");
    texture8 = LoadTexture("resources/player1/8.png");
    texture9 = LoadTexture("resources/player1/9.png");
    texture10 = LoadTexture("resources/player1/10.png");
    texture11 = LoadTexture("resources/player1/11.png");
    texture12 = LoadTexture("resources/player1/12.png");
    texture13 = LoadTexture("resources/player1/13.png");
    texture14 = LoadTexture("resources/player1/14.png");
    texture15 = LoadTexture("resources/player1/15.png");
    texture16 = LoadTexture("resources/player1/16.png");
    texture17 = LoadTexture("resources/player1/17.png");
    texture18 = LoadTexture("resources/player1/18.png");
    texture19 = LoadTexture("resources/player1/19.png");
    texture20 = LoadTexture("resources/player1/20.png");
    texture21 = LoadTexture("resources/player1/21.png");

    texture22 = LoadTexture("resources/player2/1.png");
    texture23 = LoadTexture("resources/player2/2.png");
    texture24 = LoadTexture("resources/player2/3.png");
    texture25 = LoadTexture("resources/player2/4.png");
    texture26 = LoadTexture("resources/player2/5.png");
    texture27 = LoadTexture("resources/player2/6.png");
    texture28 = LoadTexture("resources/player2/7.png");
    texture29 = LoadTexture("resources/player2/8.png");
    texture30 = LoadTexture("resources/player2/9.png");
    texture31 = LoadTexture("resources/player2/10.png");
    texture32 = LoadTexture("resources/player2/11.png");
    texture33 = LoadTexture("resources/player2/12.png");
    texture34 = LoadTexture("resources/player2/13.png");
    texture35 = LoadTexture("resources/player2/14.png");
    texture36 = LoadTexture("resources/player2/15.png");
    texture37 = LoadTexture("resources/player2/16.png");
    texture38 = LoadTexture("resources/player2/17.png");
    texture39 = LoadTexture("resources/player2/18.png");
    texture40 = LoadTexture("resources/player2/19.png");
    texture41 = LoadTexture("resources/player2/20.png");
    texture42 = LoadTexture("resources/player2/21.png");

    dice1 = LoadTexture("resources/dice1.png");
    dice2 = LoadTexture("resources/dice2.png");
    dice3 = LoadTexture("resources/dice3.png");
    texLogo = LoadTexture("resources/logo.png");
    retro = LoadTexture("resources/retrogame.png");
    Logo = LoadTexture("resources/Title.png");

    InitAudioDevice();

    // Audio loading
    fxMenuMove = LoadSound("resources/menu_move.wav");
    fxMenuSelect = LoadSound("resources/menu_select.wav");
    fxPause = LoadSound("resources/pause.wav");
    fxEnding = LoadSound("resources/ending.wav");
    fxButton = LoadSound("resources/buttonfx.wav");
    music2 = LoadMusicStream("resources/country.mp3");
    musicTitle = LoadMusicStream("resources/music_title.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    UnloadFont(font); // Unload fonts

    // Unload sounds
    UnloadSound(fxMenuMove);
    UnloadSound(fxMenuSelect);
    UnloadSound(fxPause);
    UnloadSound(fxEnding);
    UnloadMusicStream(musicTitle);
    UnloadSound(fxButton);
    UnloadTexture(board);
    UnloadTexture(texture1);
    UnloadTexture(texLogo);
    UnloadTexture(dice1);
    UnloadTexture(dice2);
    UnloadTexture(dice3);
    UnloadTexture(retro);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
int incans(int p, int player)
{
    Texture2D P1 = LoadTexture("resources/P1.png");
    Texture2D P2 = LoadTexture("resources/P2.png");
    if (player == 1)
    {
        switch (p)
        {
        case 1:
            DrawTexture(P1, 450, 30, RAYWHITE);
            break;
        case 2:
            DrawTexture(P1, 360, 30, RAYWHITE);
            break;
        case 3:
            DrawTexture(P1, 460, 30, RAYWHITE);
            break;
        case 4:
            DrawTexture(P1, 590, 30, RAYWHITE);
            break;
        case 5:
            DrawTexture(P1, 660, 30, RAYWHITE);
            break;
        case 6:
            DrawTexture(P1, 780, 30, RAYWHITE);
            break;
        case 7:
            DrawTexture(P1, 870, 30, RAYWHITE);
            break;
        case 8:
            DrawTexture(P1, 1040, 30, RAYWHITE);
            break;
        case 9:
            DrawTexture(P1, 1040, 200, RAYWHITE);
            break;
        case 10:
            DrawTexture(P1, 1040, 300, RAYWHITE);
            break;
        case 11:
            DrawTexture(P1, 1040, 400, RAYWHITE);
            break;
        case 12:
            DrawTexture(P1, 1040, 500, RAYWHITE);
            break;
        case 13:
            DrawTexture(P1, 880, 500, RAYWHITE);
            break;
        case 14:
            DrawTexture(P1, 790, 500, RAYWHITE);
            break;
        case 15:
            DrawTexture(P1, 680, 500, RAYWHITE);
            break;
        case 16:
            DrawTexture(P1, 580, 500, RAYWHITE);
            break;
        case 17:
            DrawTexture(P1, 480, 520, RAYWHITE);
            break;
        case 18:
            DrawTexture(P1, 390, 500, RAYWHITE);
            break;
        case 19:
            DrawTexture(P1, 160, 520, RAYWHITE);
            break;
        case 20:
            DrawTexture(P1, 190, 520, RAYWHITE);
            break;
        case 21:
            DrawTexture(P1, 100, 400, RAYWHITE);
            break;
        }
    }
    else
    {
        switch (p)
        {
        case 1:
            DrawTexture(P2, 200, 30, RAYWHITE);
            break;
        case 2:
            DrawTexture(P2, 340, 30, RAYWHITE);
            break;
        case 3:
            DrawTexture(P2, 490, 30, RAYWHITE);
            break;
        case 4:
            DrawTexture(P2, 590, 30, RAYWHITE);
            break;
        case 5:
            DrawTexture(P2, 690, 30, RAYWHITE);
            break;
        case 6:
            DrawTexture(P2, 810, 30, RAYWHITE);
            break;
        case 7:
            DrawTexture(P2, 890, 30, RAYWHITE);
            break;
        case 8:
            DrawTexture(P2, 1000, 30, RAYWHITE);
            break;
        case 9:
            DrawTexture(P2, 1000, 200, RAYWHITE);
            break;
        case 10:
            DrawTexture(P2, 1000, 300, RAYWHITE);
            break;
        case 11:
            DrawTexture(P2, 1000, 400, RAYWHITE);
            break;
        case 12:
            DrawTexture(P2, 1000, 500, RAYWHITE);
            break;
        case 13:
            DrawTexture(P2, 890, 500, RAYWHITE);
            break;
        case 14:
            DrawTexture(P2, 790, 500, RAYWHITE);
            break;
        case 15:
            DrawTexture(P2, 690, 500, RAYWHITE);
            break;
        case 16:
            DrawTexture(P2, 590, 500, RAYWHITE);
            break;
        case 17:
            DrawTexture(P2, 490, 500, RAYWHITE);
            break;
        case 18:
            DrawTexture(P2, 390, 500, RAYWHITE);
            break;
        case 19:
            DrawTexture(P2, 160, 500, RAYWHITE);
            break;
        case 20:
            DrawTexture(P2, 190, 500, RAYWHITE);
            break;
        case 21:
            DrawTexture(P2, 100, 400, RAYWHITE);
            break;
        }
    }
}
// Update and draw game frame
static void UpdateDrawFrame(void)
{
    switch (currentScreen)
    {
    case GAMEPLAY:
    {
        PlayMusicStream(music2);
        if (player == 1)
        {
            if (IsKeyPressed(KEY_R))
            {
                p1 = GetRandomValue(1, 3);
                dice = p1;
                p1ques += p1;
                p1Prev = p1ques - p1;
                PlaySound(fxButton);
                player++;
            }
        }
        else
        {
            if (IsKeyPressed(KEY_T))
            {
                p2 = GetRandomValue(1, 3);
                dice = p2;
                p2ques += p2;
                p2Prev = p2ques - p2;
                PlaySound(fxButton);
                player--;
            }
        }

        // In-game menu logic
        if (IsKeyPressed(KEY_SPACE))
        {
            showInGameMenu = !showInGameMenu;
            PlaySound(fxPause);
        }
        else
        {
            if (IsKeyPressed(KEY_DOWN))
            {
                optionSelect++;
                PlaySound(fxMenuMove);
            }
            else if (IsKeyPressed(KEY_UP))
            {
                optionSelect--;
                PlaySound(fxMenuMove);
            }

            if (optionSelect < 0)
                optionSelect = 0;
            else if (optionSelect > 2)
                optionSelect = 2;

            if (IsKeyPressed(KEY_ENTER))
            {
                if (optionSelect == 0)
                    showInGameMenu = false; // Resume game
                else if (optionSelect == 1)
                {
                    endingResult = 0;
                    showInGameMenu = false;
                    currentScreen = ENDING; // Title screen
                    StopMusicStream(music2);
                }
                else if (optionSelect == 2)
                {
                    currentScreen = CREDITS;
                }

                framesCounter = 0;
                PlaySound(fxMenuSelect);
            }
        }
        UpdateMusicStream(music2);

        timePlayed1 = GetMusicTimePlayed(music2) / GetMusicTimeLength(music2) * 400;

        if (timePlayed1 > 400)
            StopMusicStream(music2);
        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            mouseOnText = true;
        else
            mouseOnText = false;

        if (mouseOnText)
        {

            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {

                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    p1Ans[letterCount] = (char)key;
                    p1Ans[letterCount + 1] = '\0';
                    letterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0)
                    letterCount = 0;
                p1Ans[letterCount] = '\0';
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;
        // player 2-----------------------------------------------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), p2textBox))
            damouseOnText = true;
        else
            damouseOnText = false;

        if (damouseOnText)
        {

            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0)
            {

                if ((key >= 32) && (key <= 125) && (p2letterCount < MAX_INPUT_CHARS))
                {
                    p2Ans[p2letterCount] = (char)key;
                    p2Ans[p2letterCount + 1] = '\0';
                    p2letterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE))
            {
                p2letterCount--;
                if (p2letterCount < 0)
                    p2letterCount = 0;
                p2Ans[p2letterCount] = '\0';
            }
        }
        else
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (damouseOnText)
            p2framesCounter++;
        else
            p2framesCounter = 0;
    }
    break;
    case CREDITS:
    {
        PlayMusicStream(musicTitle);
        UpdateMusicStream(musicTitle);

        creditsScrollingPosY -= 0.6f;
        if (creditsScrollingPosY < (-screenHeight + 36))
            creditsScrollingPosY = -screenHeight + 36;

        if (IsKeyPressed(KEY_ENTER))
        {
            currentScreen = GAMEPLAY;
            framesCounter = 0;
            PlaySound(fxMenuSelect);

            PlayMusicStream(music2);
        }
    }
    break;
    case ENDING:
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            musicTitle = LoadMusicStream("resources/music_title.mp3");
            currentScreen = CREDITS;
            framesCounter = 0;
            endingResult = 0;
            PlaySound(fxMenuSelect);

            creditsScrollingPosY = (float)screenHeight + 20.0f;
            PlayMusicStream(musicTitle);
        }
    }
    break;
    default:
        break;
    }
    // Draw
    //----------------------------------------------------------------------------------

    BeginDrawing();

    ClearBackground(BLACK);

    switch (currentScreen)
    {
    case GAMEPLAY:
    {

        ClearBackground(BLACK);
        Texture2D P1 = LoadTexture("resources/P1.png");
        Texture2D P2 = LoadTexture("resources/P2.png");
        DrawTexture(board, 2, 0, RAYWHITE);

        DrawText(TextFormat("PLAYER 1 ROLLED : %i", p1), 200, 250, 20, BLUE);
        DrawText(TextFormat("PLAYER 2 ROLLED : %i", p2), 200, 280, 20, MAROON);

        DrawText("PLAYER 1: CLICK R to TO ROLL THE DICE", 200, 360, 8, DARKGRAY);
        DrawText("PLAYER 2: CLICK T to TO ROLL THE DICE", 200, 380, 8, DARKGRAY);

        DrawRectangleRec(textBox, WHITE);
        if (mouseOnText)
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);
        else
            DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

        DrawText(p1Ans, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLUE);

        if (mouseOnText)
        {
            if (letterCount < MAX_INPUT_CHARS)
            {
                if (((framesCounter / 20) % 2) == 0)
                    DrawText("_", (int)textBox.x + 8 + MeasureText(p1Ans, 40), (int)textBox.y + 12, 40, BLUE);
            }
            else
                DrawText("", 230, 300, 20, GRAY);
        }

        DrawRectangleRec(p2textBox, WHITE);
        if (damouseOnText)
            DrawRectangleLines((int)p2textBox.x, (int)p2textBox.y, (int)p2textBox.width, (int)p2textBox.height, RED);
        else
            DrawRectangleLines((int)p2textBox.x, (int)p2textBox.y, (int)p2textBox.width, (int)p2textBox.height, DARKGRAY);

        DrawText(p2Ans, (int)p2textBox.x + 5, (int)p2textBox.y + 8, 40, MAROON);

        if (damouseOnText)
        {
            if (p2letterCount < MAX_INPUT_CHARS)
            {

                if (((p2framesCounter / 20) % 2) == 0)
                    DrawText("_", (int)p2textBox.x + 8 + MeasureText(p2Ans, 40), (int)p2textBox.y + 12, 40, MAROON);
            }
            else
                DrawText("", 230, 300, 20, GRAY);
        }
        switch (dice)
        {
        case 1:
            DrawTexture(dice1, 260, 310, WHITE);
            break;
        case 2:
            DrawTexture(dice2, 260, 305, WHITE);
            break;
        case 3:
            DrawTexture(dice3, 260, 310, WHITE);
            break;
        }
        switch (p2ques)
        {
        case 0:
            DrawTexture(P1, 100, 30, RAYWHITE);
            break;
        case 1:
            DrawTexture(texture1, 450, 160, WHITE);
            if (p2Ans[0] == 'a')
            {
                DrawTexture(P1, 250, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 2:
            DrawTexture(texture2, 450, 160, WHITE);
            if (p2Ans[0] == 'a')
            {
                DrawTexture(P1, 360, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 3:
            DrawTexture(texture3, 450, 160, WHITE);
            if (p2Ans[0] == 'c')
            {
                DrawTexture(P1, 460, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 4:
            DrawTexture(texture4, 450, 160, WHITE);
            if (p2Ans[0] == 'd')
            {
                DrawTexture(P1, 590, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 5:
            DrawTexture(texture5, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 690, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 6:
            DrawTexture(texture6, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 790, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 7:
            DrawTexture(texture7, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 870, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 8:
            DrawTexture(texture8, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 990, 30, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 9:
            DrawTexture(texture9, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 990, 200, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 10:
            DrawTexture(texture10, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 990, 300, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 11:
            DrawTexture(texture11, 450, 160, WHITE);
            if (p2Ans[0] == 'c')
            {
                DrawTexture(P1, 990, 400, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 12:
            DrawTexture(texture12, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 990, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 13:
            DrawTexture(texture13, 450, 160, WHITE);
            if (p2Ans[0] == 'a')
            {
                DrawTexture(P1, 890, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 14:
            DrawTexture(texture14, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 790, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }

            break;
        case 15:
            DrawTexture(texture15, 450, 160, WHITE);
            if (p2Ans[0] == 'd')
            {
                DrawTexture(P1, 690, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 16:
            DrawTexture(texture16, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 590, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 17:
            DrawTexture(texture17, 450, 160, WHITE);
            if (p2Ans[0] == 'c')
            {
                DrawTexture(P1, 490, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 18:
            DrawTexture(texture18, 450, 160, WHITE);
            if (p2Ans[0] == 'd')
            {
                DrawTexture(P1, 390, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }

            break;
        case 19:
            DrawTexture(texture19, 450, 160, WHITE);
            if (p2Ans[0] == 'a')
            {
                DrawTexture(P1, 290, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 20:
            DrawTexture(texture20, 450, 160, WHITE);
            if (p2Ans[0] == 'a')
            {
                DrawTexture(P1, 190, 500, RAYWHITE);
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        case 21:
            DrawTexture(texture21, 450, 160, WHITE);
            if (p2Ans[0] == 'b')
            {
                DrawTexture(P1, 100, 400, RAYWHITE);
                endingResult = 1;
                currentScreen = ENDING;
            }
            else
            {
                int p = p2ques - p2;
                incans(p, player);
            }
            break;
        default:
            endingResult = 1;
            currentScreen = ENDING;
        }
        switch (p1ques)
        {
        case 0:
            DrawTexture(P2, 110, 30, RAYWHITE);
            break;
        case 1:
            DrawTexture(texture22, 720, 160, WHITE);
            if (p1Ans[0] == 'd')
            {
                DrawTexture(P2, 200, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 2:
            DrawTexture(texture23, 720, 160, WHITE);
            if (p1Ans[0] == 'b')
            {
                DrawTexture(P2, 340, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 3:
            DrawTexture(texture24, 720, 160, WHITE);
            if (p1Ans[0] == 'b')
            {
                DrawTexture(P2, 490, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 4:
            DrawTexture(texture25, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 590, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 5:
            DrawTexture(texture26, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 710, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 6:
            DrawTexture(texture27, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 790, 30, RAYWHITE);
            }
            else
            {

                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 7:
            DrawTexture(texture28, 720, 160, WHITE);
            if (p1Ans[0] == 'c')
            {
                DrawTexture(P2, 890, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 8:
            DrawTexture(texture29, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 990, 30, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 9:
            DrawTexture(texture30, 720, 170, WHITE);
            if (p1Ans[0] == 'd')
            {
                DrawTexture(P2, 990, 200, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 10:
            DrawTexture(texture31, 720, 160, WHITE);
            if (p1Ans[0] == 'b')
            {
                DrawTexture(P2, 990, 300, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 11:
            DrawTexture(texture32, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 990, 400, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 12:
            DrawTexture(texture33, 720, 160, WHITE);
            if (p1Ans[0] == 'c')
            {
                DrawTexture(P2, 990, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 13:
            DrawTexture(texture34, 720, 160, WHITE);
            if (p1Ans[0] == 'b')
            {
                DrawTexture(P2, 890, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 14:
            DrawTexture(texture35, 720, 160, WHITE);
            if (p1Ans[0] == 'd')
            {
                DrawTexture(P2, 790, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 15:
            DrawTexture(texture36, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 690, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 16:
            DrawTexture(texture37, 720, 160, WHITE);
            if (p1Ans[0] == 'b')
            {
                DrawTexture(P2, 590, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 17:
            DrawTexture(texture38, 720, 160, WHITE);
            if (p1Ans[0] == 'c')
            {
                DrawTexture(P2, 490, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 18:
            DrawTexture(texture39, 720, 160, WHITE);
            if (p1Ans[0] == 'd')
            {
                DrawTexture(P2, 390, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 19:
            DrawTexture(texture40, 720, 160, WHITE);
            if (p1Ans[0] == 'c')
            {
                DrawTexture(P2, 290, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 20:
            DrawTexture(texture41, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 190, 500, RAYWHITE);
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        case 21:
            DrawTexture(texture42, 720, 160, WHITE);
            if (p1Ans[0] == 'a')
            {
                DrawTexture(P2, 100, 400, RAYWHITE);
                endingResult = 2;
                currentScreen = ENDING;
            }
            else
            {
                int p = p1ques - p1;
                incans(p, player);
            }
            break;
        default:
            endingResult = 2;
            currentScreen = ENDING;

            break;
        }
        DrawText("PLAYER 1", 790, 170, 30, WHITE);
        DrawText("PLAYER 2", 500, 170, 30, WHITE);
        if (showInGameMenu)
        {

            DrawRectangle(0, 300, screenWidth, 84, DARKGRAY);
            DrawRectangle(screenWidth / 2 - 65, 310 + optionSelect * 16, 130, 16, BLACK);
            DrawTextEx(font, "RESUME GAME", (Vector2){screenWidth / 2 - MeasureTextEx(font, "RESUME GAME", font.baseSize, 2).x / 2, 102 + 210}, font.baseSize, 2, (optionSelect == 0) ? GB_GREEN03 : GB_GREEN02);
            DrawTextEx(font, "RESTART GAME", (Vector2){screenWidth / 2 - MeasureTextEx(font, "BACK TO TITLE", font.baseSize, 2).x / 2, 102 + 225}, font.baseSize, 2, (optionSelect == 1) ? GB_GREEN03 : GB_GREEN02);
            DrawTextEx(font, "CREDITS", (Vector2){screenWidth / 2 - MeasureTextEx(font, "EXIT GAME", font.baseSize, 2).x / 2, 102 + 240}, font.baseSize, 2, (optionSelect == 2) ? GB_GREEN03 : GB_GREEN02);
        }
    }
    break;

    case CREDITS:
    {

        DrawTexture(retro, 235, 150, WHITE);
        // Draw scrolling credits
        DrawTextEx(font, " GAME PROGRAMMING ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " GAME PROGRAMMING ", font.baseSize, 2).x / 2, creditsScrollingPosY}, font.baseSize, 5, DARKGRAY);
        DrawTextEx(font, " Aeron Justin Quiambao (AJ) ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Aeron Justin Quiambao (AJ) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 20}, font.baseSize, 5, WHITE);
        DrawTextEx(font, " Alfredo Dacquel (DAQ) ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Alfredo Dacquel (DAQ) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 40}, font.baseSize, 5, WHITE);
        DrawTextEx(font, " Ritchelle T. Rueras (CHELLEE) ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Ritchelle T. Rueras (CHELLEE) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 60}, font.baseSize, 5, WHITE);
        DrawTextEx(font, " Jeanne Zxell Caballes (JE-AN) ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Jeanne Zxell Caballes (JE-AN) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 80}, font.baseSize, 5, WHITE);
        DrawTextEx(font, " Monique Kyle Cabigting (MONIQ) ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Monique Kyle Cabigting (MONIQ) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 100}, font.baseSize, 5, WHITE);

        DrawTextEx(font, " GAME DESIGN \n", (Vector2){screenWidth / 2 - MeasureTextEx(font, " GAME DESIGN ", font.baseSize, 2).x / 2, creditsScrollingPosY + 240}, font.baseSize, 5, DARKGRAY);
        DrawTextEx(font, " Ritchelle T. Rueras (CHELLEE) \n", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Ritchelle T. Rueras (CHELLEE) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 260}, font.baseSize, 5, WHITE);

        DrawTextEx(font, " GAME ART \n", (Vector2){screenWidth / 2 - MeasureTextEx(font, " GAME ART ", font.baseSize, 2).x / 2, creditsScrollingPosY + 320}, font.baseSize, 5, DARKGRAY);
        DrawTextEx(font, " Jeanne Xhell Caballes (JE-AN) \n", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Jeanne Xhell Caballes (JE-AN) ", font.baseSize, 2).x / 2, creditsScrollingPosY + 340}, font.baseSize, 5, WHITE);

        DrawTextEx(font, " GAME AUDIO \n", (Vector2){screenWidth / 2 - MeasureTextEx(font, " GAME AUDIO \n", font.baseSize, 2).x / 2, creditsScrollingPosY + 400}, font.baseSize, 5, DARKGRAY);
        DrawTextEx(font, " Monique Kyle Cabigting ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " Monique Kyle Cabigting ", font.baseSize, 2).x / 2, creditsScrollingPosY + 420}, font.baseSize, 5, WHITE);

        DrawTextEx(font, "powered by", (Vector2){screenWidth / 2 - MeasureTextEx(font, "powered by", font.baseSize, 2).x / 2, creditsScrollingPosY + 500}, font.baseSize, 5, DARKGRAY);
        DrawTexture(texLogo, screenWidth / 2 - 64, creditsScrollingPosY + 550, WHITE);
        DrawTextEx(font, " GAME: ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " GAME TITLE: ", font.baseSize, 2).x / 2, creditsScrollingPosY + 770}, font.baseSize, 5, DARKGRAY);
        DrawTexture(Logo, screenWidth / 2 - 64, creditsScrollingPosY + 790, WHITE);

        DrawRectangle(screenWidth - 60, screenHeight - 24, 50, 16, GB_GREEN02);
        DrawTextEx(font, "BACK", (Vector2){screenWidth - 50, screenHeight - 22}, font.baseSize, 2, GB_GREEN03);
    }
    break;
    case ENDING:
    {
        DrawTexture(retro, 235, 150, WHITE);
        if (endingResult == 1)
        {
            DrawTextEx(font, " WE HAVE A WINNER!!! ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " WE HAVE A WINNER!!! ", font.baseSize * 2, 2).x / 2, 100}, font.baseSize * 2, 2, GB_GREEN03);
        }
        else
            DrawTextEx(font, " PRESS ENTER TO CONTINUE ", (Vector2){screenWidth / 2 - MeasureTextEx(font, " PRESS ENTER TO CONTINUE ", font.baseSize * 2, 2).x / 2, 100}, font.baseSize * 2, 2, GB_GREEN03);

        DrawRectangle(screenWidth / 2 - 65, 170, 130, 16, GB_GREEN02);
        DrawTextEx(font, "CONTINUE", (Vector2){screenWidth / 2 - MeasureTextEx(font, "CONTINUE", font.baseSize, 2).x / 2, 172}, font.baseSize, 2, GB_GREEN03);
    }
    break;
    default:
        break;
    } //
    EndDrawing();
}

int main()
{
    lobby();
    instructions();
    maingame();
}
