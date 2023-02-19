#include <iostream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>  
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <random>

using namespace std;
using namespace sf;


const int M = 19;
const int N = 10;

struct Point {
    int x,y;
    } a[4], b[4];


int field[M][N] = {0};
int figures[7][4] = {
    1,3,5,7,
    2,4,5,7, 
    3,5,4,6,
    3,5,4,7,
    2,3,5,7,
    3,5,7,6,
    2,3,4,5,
};

bool check ()
    {
        for (int i = 0; i < 4; i++)
            if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) {
                return 0;
            }
            else if (field[a[i].y][a[i].x]) {
                return 0;
            }
            return 1;
    };



int main () {
    srand(time(0));
    RenderWindow window(VideoMode(1280,1655), "Tetris Remake!");
    
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("orb2.wav"))
        return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sound.setLoop(true);
    

    Texture highReso,backGround;
    highReso.loadFromFile("tilesRemade.png");
    backGround.loadFromFile("tetrisBoard.png");

    Sprite s(highReso), ba(backGround);

    int dx = 0;
    bool rotate = 0;
    int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event start;
        while (window.pollEvent(start)) {
            if (start.type == Event::Closed)
                window.close();
                
            if (start.type == Event::KeyPressed) {
                if (start.key.code == Keyboard::Up) {
                    rotate = true;
                }
                else if (start.key.code == Keyboard::Left) {
                    dx = -1;
                }
                else if (start.key.code == Keyboard::Right) {
                    dx = 1;
                }
            }
        }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        delay = 0.05;
    }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
        delay = 0.02;
    }

    /////Move //
    for (int i = 0; i < 4; i++) {
        b[i]=a[i]; 
        a[i].x += dx;
    } 
    if (!check()) {
        for (int i = 0; i < 4; i++) {
            a[i] = b[i];
        }
    }

    /////Rotate/////
    if (rotate) {
        Point p = a[1]; //center of rotation
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - p.y;
            int y = a[i].x - p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }
        if (!check()) {
            for (int i = 0; i < 4; i++) {
                a[i] = b[i];
            }
        }
        }

    /////Tick/////
    if (timer > delay)
        {
            for (int i = 0; i < 4; i++) {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!check()) {
                for (int i = 0; i < 4; i++) {
                    field[b[i].y][b[i].x] = colorNum;
                }
                    colorNum = 1 + rand()%6;
                    int n = rand()%7;
                    for (int i = 0; i < 4; i++) {
                        a[i].x = figures[n][i] % 2;
                        a[i].y = figures[n][i] / 2;
                }
            }
            

            timer = 0;
        }

    ////check lines//////
    int k = M - 1;
    for (int i = M - 1; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field[i][j]) count++;
            field[k][j] = field[i][j];
        }
        if (count < N) k--;
    }



    dx = 0;
    rotate = 0;
    delay = 0.3;

    /////////draw////////


    window.clear(Color::White);
    window.draw(ba);

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> rando(0,9);
   // int r = 1;


    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (field[i][j] == 0) {
                continue;
            }
            s.setTextureRect(IntRect(field[i][j]*97,0,97,97));
            s.setPosition(j*97,i*97);
        
            //r++;

            //while (r == 2) {
            //int randoSum = rando(generator) * 97 + 154; s.move(randoSum, -337); break;}
            
            //s.move(348, -337);
            s.move(154,-337);
            window.draw(s);
        }
    }

    for (int i = 0; i < 4; i++) {
        s.setTextureRect(IntRect(colorNum*97,0,97,97));
        s.setPosition(a[i].x*97,a[i].y*97);

        

        //while (r == 2) {
        //int randoSum = rando(generator) * 97 + 154; s.move(randoSum, -337); break;}

        //s.move(348,-337);
        s.move(154,-337);
        window.draw(s);
    }

    window.display();
    }

    return 0;
}