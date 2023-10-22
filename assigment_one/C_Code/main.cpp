#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// Define puzzle board dimensions and colors
const int WINDOW_SIZE = 300;
const int GRID_SIZE = 3;
const int GRID_WIDTH = WINDOW_SIZE / GRID_SIZE;
const int WHITE = 0xFFFFFF;
const int BLACK = 0x000000;

std::vector<std::vector<int>> current_puzzle;

void drawGrid(SDL_Renderer* renderer) {
    for (int i = 1; i < GRID_SIZE; ++i) {
        SDL_RenderDrawLine(renderer, i * GRID_WIDTH, 0, i * GRID_WIDTH, WINDOW_SIZE);
        SDL_RenderDrawLine(renderer, 0, i * GRID_WIDTH, WINDOW_SIZE, i * GRID_WIDTH);
    }
}

void drawPuzzle(SDL_Renderer* renderer, std::vector<std::vector<int>> puzzle) {
    TTF_Font* font = TTF_OpenFont("arial.ttf", 36);
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            int cell_value = puzzle[row][col];
            if (cell_value != 0) {
                std::string cell_text = std::to_string(cell_value);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, cell_text.c_str(), {0, 0, 0});
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_Rect cellRect;
                cellRect.x = col * GRID_WIDTH + GRID_WIDTH / 2 - textSurface->w / 2;
                cellRect.y = row * GRID_WIDTH + GRID_WIDTH / 2 - textSurface->h / 2;
                cellRect.w = textSurface->w;
                cellRect.h = textSurface->h;
                SDL_RenderCopy(renderer, textTexture, nullptr, &cellRect);
                SDL_DestroyTexture(textTexture);
                SDL_FreeSurface(textSurface);
            }
        }
    }
    TTF_CloseFont(font);
}

void visualizePuzzle(std::vector<std::vector<int>> puzzle, SDL_Renderer* renderer) {
    current_puzzle = puzzle;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawGrid(renderer);
    drawPuzzle(renderer, puzzle);
    SDL_RenderPresent(renderer);
}

void visualizePath(std::vector<std::vector<std::vector<int>>>& path, SDL_Renderer* renderer) {
    for (const auto& puzzle : path) {
        visualizePuzzle(puzzle, renderer);
        SDL_Delay(1000);
    }
}

void puzzleThread(SDL_Renderer* renderer) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("8-Puzzle Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
}

void startPuzzleThread(SDL_Renderer* renderer) {
    std::thread thread(puzzleThread, renderer);
    thread.detach();
}

void stopPuzzleThread() {
    // Clean up SDL and TTF
    SDL_Quit();
    TTF_Quit();
}

class Node {
public:
    static const int GRID_SIZE = 3;

    Node(std::vector<std::vector<int>> state) {
        this->state = state;
        this->parent = nullptr;
        this->path = {};
        this->generateChildren();
    }

    void generateChildren() {
        children.clear();
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (state[i][j] == 0) {
                    if (i > 0) {
                        children.push_back(swap(i, j, i - 1, j));
                    }
                    if (i < GRID_SIZE - 1) {
                        children.push_back(swap(i, j, i + 1, j));
                    }
                    if (j > 0) {
                        children.push_back(swap(i, j, i, j - 1));
                    }
                    if (j < GRID_SIZE - 1) {
                        children.push_back(swap(i, j, i, j + 1));
                    }
                    return;
                }
            }
        }
    }

    std::vector<std::vector<int>> swap(int x1, int y1, int x2, int y2) {
        std::vector<std::vector<int>> newState = state;
        std::swap(newState[x1][y1], newState[x2][y2]);
        return newState;
    }

    void setParent(Node* parentNode) {
        parent = parentNode;
        path = parent->getPath();
        path.push_back(parent);
    }

    std::vector<Node*> getPath() {
        return path;
    }

    std::vector<std::vector<int>> getState() {
        return state;
    }

    std::vector<std::vector<std::vector<int>>> getChildren() {
        return children;
    }

private:
    std::vector<std::vector<int>> state;
    Node* parent;
    std::vector<Node*> path;
    std::vector<std::vector<std::vector<int>>> children;
};

std::vector<std::vector<int>> BFS(std::vector<std::vector<int>> initialState, std::vector<std::vector<int>> targetState) {
    std::queue<Node*> queue;
    std::unordered_set<std::vector<std::vector<int>>> visited;

    Node* initialNode = new Node(initialState);
    queue.push(initialNode);
    visited.insert(initialState);

    while (!queue.empty()) {
        Node* currentNode = queue.front();
        queue.pop();
        std::vector<std::vector<int>> currentState = currentNode->getState();

        if (currentState == targetState) {
            std::vector<std::vector<int>> finalPath;
            finalPath = currentNode->getPath();
            finalPath.push_back(currentNode);
            return finalPath;
        }

        for (const auto& childState : currentNode->getChildren()) {
            if (visited.find(childState) == visited.end()) {
                Node* childNode = new Node(childState);
                childNode->setParent(currentNode);
                queue.push(childNode);
                visited.insert(childState);
            }
        }
    }

    return {};
}

int main() {
    std::vector<std::vector<int>> target = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8}#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

// Define puzzle board dimensions and colors
            const int WINDOW_SIZE = 300;
            const int GRID_SIZE = 3;
            const int GRID_WIDTH = WINDOW_SIZE / GRID_SIZE;
            const int WHITE = 0xFFFFFF;
            const int BLACK = 0x000000;

            std::vector<std::vector<int>> current_puzzle;

            void drawGrid(SDL_Renderer* renderer) {
                for (int i = 1; i < GRID_SIZE; ++i) {
                    SDL_RenderDrawLine(renderer, i * GRID_WIDTH, 0, i * GRID_WIDTH, WINDOW_SIZE);
                    SDL_RenderDrawLine(renderer, 0, i * GRID_WIDTH, WINDOW_SIZE, i * GRID_WIDTH);
                }
            }

            void drawPuzzle(SDL_Renderer* renderer, std::vector<std::vector<int>> puzzle) {
                TTF_Font* font = TTF_OpenFont("arial.ttf", 36);
                for (int row = 0; row < GRID_SIZE; ++row) {
                    for (int col = 0; col < GRID_SIZE; ++col) {
                        int cell_value = puzzle[row][col];
                        if (cell_value != 0) {
                            std::string cell_text = std::to_string(cell_value);
                            SDL_Surface* textSurface = TTF_RenderText_Solid(font, cell_text.c_str(), {0, 0, 0});
                            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                            SDL_Rect cellRect;
                            cellRect.x = col * GRID_WIDTH + GRID_WIDTH / 2 - textSurface->w / 2;
                            cellRect.y = row * GRID_WIDTH + GRID_WIDTH / 2 - textSurface->h / 2;
                            cellRect.w = textSurface->w;
                            cellRect.h = textSurface->h;
                            SDL_RenderCopy(renderer, textTexture, nullptr, &cellRect);
                            SDL_DestroyTexture(textTexture);
                            SDL_FreeSurface(textSurface);
                        }
                    }
                }
                TTF_CloseFont(font);
            }

            void visualizePuzzle(std::vector<std::vector<int>> puzzle, SDL_Renderer* renderer) {
                current_puzzle = puzzle;

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                drawGrid(renderer);
                drawPuzzle(renderer, puzzle);
                SDL_RenderPresent(renderer);
            }

            void visualizePath(std::vector<std::vector<std::vector<int>>>& path, SDL_Renderer* renderer) {
                for (const auto& puzzle : path) {
                    visualizePuzzle(puzzle, renderer);
                    SDL_Delay(1000);
                }
            }

            void puzzleThread(SDL_Renderer* renderer) {
                SDL_Init(SDL_INIT_EVERYTHING);
                TTF_Init();
                SDL_Window* window = SDL_CreateWindow("8-Puzzle Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, 0);
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

                bool quit = false;
                SDL_Event e;
                while (!quit) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    }
                }

                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                TTF_Quit();
            }

            void startPuzzleThread(SDL_Renderer* renderer) {
                std::thread thread(puzzleThread, renderer);
                thread.detach();
            }

            void stopPuzzleThread() {
                // Clean up SDL and TTF
                SDL_Quit();
                TTF_Quit();
            }

            class Node {
                public:
                static const int GRID_SIZE = 3;

                Node(std::vector<std::vector<int>> state) {
                    this->state = state;
                    this->parent = nullptr;
                    this->path = {};
                    this->generateChildren();
                }

                void generateChildren() {
                    children.clear();
                    for (int i = 0; i < GRID_SIZE; ++i) {
                        for (int j = 0; j < GRID_SIZE; ++j) {
                            if (state[i][j] == 0) {
                                if (i > 0) {
                                    children.push_back(swap(i, j, i - 1, j));
                                }
                                if (i < GRID_SIZE - 1) {
                                    children.push_back(swap(i, j, i + 1, j));
                                }
                                if (j > 0) {
                                    children.push_back(swap(i, j, i, j - 1));
                                }
                                if (j < GRID_SIZE - 1) {
                                    children.push_back(swap(i, j, i, j + 1));
                                }
                                return;
                            }
                        }
                    }
                }

                std::vector<std::vector<int>> swap(int x1, int y1, int x2, int y2) {
                    std::vector<std::vector<int>> newState = state;
                    std::swap(newState[x1][y1], newState[x2][y2]);
                    return newState;
                }

                void setParent(Node* parentNode) {
                    parent = parentNode;
                    path = parent->getPath();
                    path.push_back(parent);
                }

                std::vector<Node*> getPath() {
                    return path;
                }

                std::vector<std::vector<int>> getState() {
                    return state;
                }

                std::vector<std::vector<std::vector<int>>> getChildren() {
                    return children;
                }

                private:
                std::vector<std::vector<int>> state;
                Node* parent;
                std::vector<Node*> path;
                std::vector<std::vector<std::vector<int>>> children;
            };

            std::vector<std::vector<int>> BFS(std::vector<std::vector<int>> initialState, std::vector<std::vector<int>> targetState) {
                std::queue<Node*> queue;
                std::unordered_set<std::vector<std::vector<int>>> visited;

                Node* initialNode = new Node(initialState);
                queue.push(initialNode);
                visited.insert(initialState);

                while (!queue.empty()) {
                    Node* currentNode = queue.front();
                    queue.pop();
                    std::vector<std::vector<int>> currentState = currentNode->getState();

                    if (currentState == targetState) {
                        std::vector<std::vector<int>> finalPath;
                        finalPath = currentNode->getPath();
                        finalPath.push_back(currentNode);
                        return finalPath;
                    }

                    for (const auto& childState : currentNode->getChildren()) {
                        if (visited.find(childState) == visited.end()) {
                            Node* childNode = new Node(childState);
                            childNode->setParent(currentNode);
                            queue.push(childNode);
                            visited.insert(childState);
                        }
                    }
                }

                return {};
            }

            int main() {
                std::vector<std::vector<int>> target = {
                        {0, 1, 2},
                        {3, 4, 5},
                        {6, 7, 8}
                };

                std::vector<std::vector<int>> puzzle1 = {
                        {1, 2, 5},
                        {3, 7, 0},
                        {6, 4, 8}
                };

                std::vector<std::vector<std::vector<int>>> path = BFS(puzzle1, target);
                SDL_Renderer* renderer = nullptr;
                startPuzzleThread(renderer);
                visualizePath(path, renderer);

                // Clean up SDL and TTF
                stopPuzzleThread();

                return 0;
            }

    };

    std::vector<std::vector<int>> puzzle1 = {
            {1, 2, 5},
            {3, 7, 0},
            {6, 4, 8}
    };

    std::vector<std::vector<std::vector<int>>> path = BFS(puzzle1, target);
    SDL_Renderer* renderer = nullptr;
    startPuzzleThread(renderer);
    visualizePath(path, renderer);

    // Clean up SDL and TTF
    stopPuzzleThread();

    return 0;
}

