#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int left;
    int right;
} App;

typedef struct
{
    int x;
    int y;
    SDL_Texture *texture;
} Entity;

App app;
Entity entity;

SDL_Texture *loadTexture(void *pixels, int width, int height)
{
    SDL_Texture *texture = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture)
    {
        printf("Failed to create texture: %s\n", SDL_GetError());
        exit(1);
    }
    // Update the texture with the pixel data
    SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
    return texture;
}

void doKeyUp(SDL_KeyboardEvent *event);
void doKeyDown(SDL_KeyboardEvent *event);

void doInput(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
            doKeyDown(&event.key);
            break;
        case SDL_KEYUP:
            doKeyUp(&event.key); // Call doKeyUp function here
            break;
        default:
            break;
        }
    }
}

void doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 1;
        }
    }
}

void doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 0;
        }
    }
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

void initSDL(void)
{
    int rendererFlags, windowFlags;
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = 0;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanup()
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(App));
    memset(&entity, 0, sizeof(Entity));
    initSDL();
    entity.x = 250;
    entity.y = 250;
    Uint32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT] = {0};
    entity.texture = loadTexture(pixels, entity.x, entity.y);
    atexit(cleanup);
    while (1)
    {
        prepareScene();
        doInput();

        if (app.up)
        {
            entity.y -= 4;
        }

        if (app.down)
        {
            entity.y += 4;
        }

        if (app.left)
        {
            entity.x -= 4;
        }

        if (app.right)
        {
            entity.x += 4;
        }

        blit(entity.texture, entity.x, entity.y);
        presentScene();
        SDL_Delay(16);
    }
    return 0;
}