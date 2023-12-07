#include <SDL.h>
#include "utils/Window.h"
#include "utils/Layer.h"
#include "utils/Button.h"
#include "utils/Application.h"

int main() {
  Window GameWindow;
  Application App { &GameWindow };
  Layer UI;
  Button ExampleButton { &App };
  UI.SubscribeToEvents(&ExampleButton);

  SDL_Event Event;
  while(true) {
    while(SDL_PollEvent(&Event)) {
      if (Event.type == SDL_QUIT) {
        SDL_Quit();
        return 0;
      }
      if (UI.HandleEvent(&Event)) {
        continue;
      }
    }
    GameWindow.RenderFrame();
  }
}
