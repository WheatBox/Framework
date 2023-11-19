
/* THIS IS JUST FOR TEST NOW */

#include <SDL.h>

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void Rotate(int * pAngle) {
	/* Test for Edit & Continue */
	(* pAngle)++;
}

int
nothing(int argc, char ** argv)
//main(int argc, char ** argv)
{
	argc, argv;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window;
	SDL_Renderer * renderer;

	SDL_CreateWindowAndRenderer(800, 600, 0, & window, & renderer);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	srand((unsigned int)time(0));

	SDL_Point points[100];
	for(int i = 0; i < 100; i++) {
		points[i] = (SDL_Point) { .x = rand() % 800, .y = rand() % 600 };
	}

	SDL_Surface * surf = SDL_LoadBMP("Assets/spr_test.bmp");
	if(surf == NULL) {
		SDL_Log("NULL SURF! %s\n", SDL_GetError());
		return -1;
	}
	int texW = surf->w, texH = surf->h;
	SDL_Texture * tex = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	surf = NULL;

	SDL_Event event;

	int angle = 0;
	
	bool over = false;
	while(!over) {

		while(SDL_PollEvent(& event)) {
			if(event.type == SDL_QUIT) {
				over = true;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		/* for(int i = 1; i < 100; i++) {
			SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[i - 1].x, points[i - 1].y);
		} */
		SDL_RenderDrawLines(renderer, points, 100);

		int outnerRectSize = 18, innerRectSize = 12;
		for(int i = 1; i < 100; i++) {
			SDL_RenderDrawRect(renderer, & (SDL_Rect) { .x = points[i].x - outnerRectSize / 2, .y = points[i].y - outnerRectSize / 2, .w = outnerRectSize, .h = outnerRectSize });
			SDL_RenderFillRect(renderer, & (SDL_Rect) { .x = points[i].x - innerRectSize / 2, .y = points[i].y - innerRectSize / 2, .w = innerRectSize, .h = innerRectSize });
		}

		/*SDL_Rect texSrcRect = {
			.x = 84, .y = 200,
			.w = 140 - 45, .h = 149 - 114
		};*/

		SDL_Rect texDestRect = {
			.x = 400 - texW / 2, .h = 300 - texH / 2,
			.w = texW, .h = texH
			/*.x = (800 - texSrcRect.w) / 2, .y = (600 - texSrcRect.h) / 2,
			.w = texSrcRect.w, .h = texSrcRect.h*/
		};

		/*SDL_RenderCopy(renderer, tex, & texSrcRect, & texDestRect);*/
		Rotate(& angle);
		SDL_SetTextureColorMod(tex, 255, 255, 0);
		SDL_SetTextureAlphaMod(tex, 128);
		SDL_RenderCopyEx(renderer, tex, NULL, & texDestRect, angle, NULL, SDL_FLIP_NONE);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 64);
		SDL_RenderFillRect(renderer, & (SDL_Rect) { .x = 300, .y = 200, .w = 200, .h = 200 });

		SDL_RenderPresent(renderer);

		SDL_Delay(16);

	}

	SDL_DestroyTexture(tex);
	tex = NULL;

	return 0;
}
