
#ifndef __BLOC__CPP__
#define __BLOC__CPP__

    #include <SDL.h>
    #include "util.hpp"
    #include "grid.hpp"

    #define MAX_CASES_SHAPE 4
    #define DEFAULT_SHAPE_SPEED_TIME 300

    #define NEXTSHAPE_SPACE_X WINDOW_WIDTH-193
    #define NEXTSHAPE_SPACE_Y 175
    #define NEXTSHAPE_SPACE_SIZE 175

    class Bloc
    {
        private:
            char name;
            Pos position;
            int disabled;
            int drawable;
            SDL_Color color;
        public:
            Bloc() {}
            Bloc(char _name, int _l, int _c, SDL_Color _color)
            {
                name = _name; SetPos(_l, _c); disabled = 0; drawable = 1; color = _color; 
            }
            Pos GetPos() { return position; }
            void SetPos(int l, int c) { if (!IsOut(l, c)) {position.l = l; position.c = c;} }
            void SetName(char NewName) { name = NewName; }
            void SetDrawable(int value) { drawable = value; }
            void SetDisabled(int value) { disabled = value; }
            void Draw(SDL_Renderer *render, SDL_Rect RectGrid[LINES][COLS]);
            void Move(int vl, int vc, char grid[LINES][COLS]);

            int IsOut(int l, int c)
            {
                return (l < 0 || l >= LINES || c < 0 || c >= COLS);
            }
            int IsDrawable() { return drawable;}

            ~Bloc() {

            }
    };

    class Shape
    {
        protected:
            int l;
            int c;
            int bloc_number;
            Bloc *Blocs[4];
            SDL_Color color; 
            char name;
            int disabled;
            int rotate_state;

            

        public:
            Shape() {}
            void InitShape(int _l, int _c, int bloc_n, char name, SDL_Color _color);
            virtual void Init(int l, int c, char grid[LINES][COLS]);
            void InitBlocs(char name, int l, int c, SDL_Color _color);
            void Draw(SDL_Renderer *render, SDL_Rect GridRect[LINES][COLS], char grid[LINES][COLS]);
            virtual void DrawNextShape(SDL_Renderer *render);

            int SetPos(int line, int col, char grid[LINES][COLS]);
            void Move(int vl, int vc, char grid[LINES][COLS]);
            void MoveDown(Uint64 time, char grid[LINES][COLS], int *newBlocAllowed, int speedTime);
            void MoveRight(char grid[LINES][COLS]);
            void MoveLeft(char grid[LINES][COLS]);

            int IsGoodPosition(int vl, int vc, char grid[LINES][COLS]);
            int IsDown(char grid[LINES][COLS]);
            int IsOut(int l, int c);
            int IsDisabled() { return disabled == 1; }
            void DelSubShapes(int line_number, char grid[LINES][COLS]);
            int IsSemiShapeDisabled(int l, int c);

            Pos GetPosition() { return Pos {l, c}; }
            char GetName() { return name; }
            void SetShapeDisabled(int value) { if (value != 0 && value != 1) {return;} disabled = value;}
            void SetShapeDisabledGrid(char grid[LINES][COLS]);

            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]);
            virtual void Rotate(char grid[LINES][COLS]);
            void DisableGridShape(char grid[LINES][COLS]);
            void DelGridShape(char grid[LINES][COLS]);

            void DestroyBlocs() { for (int i = 0; i < bloc_number; i++) { delete[] Blocs; }}
    
            ~Shape();
    };


    class Square : public Shape
    {   
        public:
            Square() {}
            virtual void Init(int l, int c, char grid[LINES][COLS]) override;
            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]) override;
            virtual void DrawNextShape(SDL_Renderer *render);
    };

    class Line : public Shape
    {   
        public:
            Line() {}
            virtual void Init(int l, int c, char grid[LINES][COLS]) override;
            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]) override;
            virtual void Rotate(char grid[LINES][COLS]);
            virtual void DrawNextShape(SDL_Renderer *render);;

    };

    class Stair : public Shape
    {   
        public:
            Stair() {}
            virtual void Init(int l, int c, char grid[LINES][COLS]) override;
            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]) override;
            virtual void Rotate(char grid[LINES][COLS]);
            virtual void DrawNextShape(SDL_Renderer *render);
    };

    class Foot : public Shape
    {   
        public:
            Foot() {}
            virtual void Init(int l, int c, char grid[LINES][COLS]) override;
            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]) override;
            virtual void Rotate(char grid[LINES][COLS]);
            virtual void DrawNextShape(SDL_Renderer *render);
    };

    class Pyramid : public Shape
    {   
        public:
            Pyramid() {}
            virtual void Init(int l, int c, char grid[LINES][COLS]) override;
            virtual void SetGridShape(int l, int c, char grid[LINES][COLS]) override;
            virtual void Rotate(char grid[LINES][COLS]);
            virtual void DrawNextShape(SDL_Renderer *render);
    };


#endif