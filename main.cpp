#include <SDL2/SDL.h>
#include <./box2d/box2d.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PIXELS_PER_METER = 30.0f;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

b2World* gWorld = nullptr;

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Box2D Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void CloseSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

void InitBox2D() {
    b2Vec2 gravity(0.0f, 9.8f);
    gWorld = new b2World(gravity);
}

void CloseBox2D() {
    delete gWorld;
}

void RenderBody(b2Body* body) {
    b2Fixture* fixture = body->GetFixtureList();
    while (fixture) {
        b2Shape* shape = fixture->GetShape();
        if (shape->GetType() == b2Shape::e_polygon) {
            b2PolygonShape* polygonShape = static_cast<b2PolygonShape*>(shape);
            b2Vec2 vertices[4];
            for (int i = 0; i < polygonShape->m_count; ++i) {
                vertices[i] = body->GetWorldPoint(polygonShape->m_vertices[i]);
            }

            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderDrawLines(gRenderer, (SDL_Point*)vertices, polygonShape->m_count + 1);
        }
        fixture = fixture->GetNext();
    }
}

int main(int argc, char* args[]) {
    InitSDL();
    InitBox2D();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(SCREEN_WIDTH / 2 / PIXELS_PER_METER, 0);

    b2Body* body = gWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(50.0f / PIXELS_PER_METER, 50.0f / PIXELS_PER_METER);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        gWorld->Step(1.0f / 60.0f, 6, 2);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(gRenderer);

        RenderBody(body);

        SDL_RenderPresent(gRenderer);
    }

    CloseBox2D();
    CloseSDL();

    return 0;
}

