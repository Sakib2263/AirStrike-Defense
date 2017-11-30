#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include<cmath>

int main()
{

    sf::Vector2i screen(1000, 650);
    sf::RenderWindow window(sf::VideoMode(screen.x, screen.y), "AirStrike Defense", sf::Style::Close | sf::Style::Titlebar);  //not allowing to resize the window
    window.setFramerateLimit(40);

    int ii, temp,shoot = 0,score=0,lives=3, over_reason=2;

    bool draw_explo=false;
    bool draw_explo2 = false;

    //variable for handling scenes
    int scene = 0;            //initialized to 0 so the first scene starts

//textures for scene 1
    sf::Texture t6, t7, t8;
    t6.loadFromFile("bg.jpg");
    t7.loadFromFile("bg11.png");
    t8.loadFromFile("explo.png");

    //sprites for scene 1
    sf::Sprite background1, start_scr, explo;
    start_scr.setTexture(t7);
    background1.setTexture(t6);
    explo.setTexture(t8);

    t6.setSmooth(true);
    t7.setSmooth(true);

    sf::IntRect r2(0, 0, 1000, 650);
    start_scr.setTextureRect(r2);
    float start_hold = 12;

    //sizing the texture of background in scene 1
    sf::IntRect r1(100, 100, 1000, 650);
    background1.setTextureRect(r1);

    //variables for explosion animaion
    int ex_l = 192, ex_t = 0, ex_w = 192, ex_h = 192, driver = 0;    //l for left r right, h height, w width
    int ex_l2 = 192, ex_t2 = 0, ex_w2 = 192, ex_h2 = 192, driver2 = 0;

    //variables for mouse input;
    sf::Vector2i localpos;

    //loading the fonts
    sf::Font neuro, pdark, arial;
    pdark.loadFromFile("pdark.ttf");
    if (!arial.loadFromFile("arial.ttf"))
        return -7;
    if (!neuro.loadFromFile("neuro.ttf"))
        return EXIT_FAILURE;

    //designing the title (used in scene 0 and 1)
    sf::Text title;
    title.setFont(pdark);
    title.setPosition(50, 440);
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setString("Airstrike Defence");


    sf::Time elapsed;
    sf::Clock cclock;
    cclock.restart();

    //loading and playing music for first few seconds
    sf::Music music;
    if (!music.openFromFile("music1.ogg"))
        return -1; // error
    if(scene == 0)	music.play();

    //sound for shooting
    sf::SoundBuffer firebuffer;
    firebuffer.loadFromFile("fire.wav");
    sf::Sound fire_sound;
    fire_sound.setBuffer(firebuffer);

    //sound for explosion
    sf::SoundBuffer explobuffer;
    explobuffer.loadFromFile("fire2.wav");
    sf::Sound explo_sound;
    explo_sound.setBuffer(explobuffer);



    sf::Texture t2, t3, t4, t5, texp,bosst,lv2,heliv2,bg3,lvls;				////textures for scene 2(game scene)
    //loading the textures
    t2.loadFromFile("bg22.png");
    t3.loadFromFile("helis2.png");
    t4.loadFromFile("sbullet2.png");
    t5.loadFromFile("tank12.png");
    bg3.loadFromFile("bgl3.jpg");
    texp.loadFromFile("explo.png");
    bosst.loadFromFile("boss.png");
    lvls.loadFromFile("levels.png");

    sf::Sprite explo2,bglv2,helilv2,back3,boss,lvchoice;
    explo2.setTexture(texp);
    t2.setSmooth(true);
    lv2.loadFromFile("bg2.png");
    bglv2.setTexture(lv2);
    heliv2.loadFromFile("heliv2.png");
    helilv2.setTexture(heliv2);
    boss.setTexture(bosst);
    back3.setTexture(bg3);
    lvchoice.setTexture(lvls);

    int no_of_bullet = 49;
    sf::Sprite background2, heli, bulet[49], tank;


    int tankX = 50, tankY = 500,helilv2X,helilv2Y;
    helilv2X = tankX;
    helilv2Y =tankY;
    background2.setTexture(t2);
    heli.setTexture(t3);
    tank.setTexture(t5);
    tank.setPosition(tankX, tankY);           //setting initial position of the tank
    helilv2.setPosition(helilv2X,helilv2Y);    //setting initial position of the heli lvl2

    //setting bullet texture
    for (ii = 0; ii<no_of_bullet; ii++)
    {
        bulet[ii].setTexture(t4);
    }
    int bullet_no = 0;

    //variables for helicopter1
    sf::Vector2f tankpos, helipos,bosspos,helilv2pos;
    int heliD = 0, heliX = 850,bossX=850;
    heli.setPosition(heliX, 100);
    boss.setPosition(bossX,100);
    //textures, sprites and text for scene 3(game over)
    sf::Texture t10;
    t10.loadFromFile("game_over.jpg");

    sf::Sprite bg_over;
    bg_over.setTexture(t10);

    //textures, sprites and text for scene 4(HELP)
    sf::Texture helpg;
    helpg.loadFromFile("help.jpg");
    sf::Sprite helpbg;
    helpbg.setTexture(helpg);

    //textures, sprites and text for scene 5(About)
    sf::Texture aboutt;
    aboutt.loadFromFile("about.jpg");
    sf::Sprite about1;
    about1.setTexture(aboutt);

    sf::Text skip_command, skip_command2,reason1, reason2,Score, Life,High_score, Level2, Hscr;
    skip_command.setFont(arial);
    skip_command.setPosition(10, 630);
    skip_command.setCharacterSize(15);
    //skip_command.setFillColor(sf::Color::White);
    skip_command.setString("Press ENTER to skip to the main menu");
    Life.setFillColor(sf::Color::Yellow);
    Score.setFillColor(sf::Color::Yellow);

    High_score.setFillColor(sf::Color::Red);
    High_score.setFont(arial);
    High_score.setPosition(330, 450);
    High_score.setCharacterSize(50);

    Hscr.setFillColor(sf::Color::Green);
    Hscr.setFont(arial);
    Hscr.setPosition(250, 540);
    Hscr.setCharacterSize(50);

    skip_command2.setFont(arial);
    skip_command2.setPosition(880, 630);
    skip_command2.setCharacterSize(10);
    //skip_command.setFillColor(sf::Color::White);
    skip_command2.setString("Press ESC to exit");

    reason1.setFillColor(sf::Color::Black);
    reason1.setFont(arial);
    reason1.setPosition(300, 100);
    reason1.setCharacterSize(60);
    //skip_command.setFillColor(sf::Color::White);
    reason1.setString("Enemies win");

    reason2.setFillColor(sf::Color::Black);
    reason2.setFont(arial);
    reason2.setPosition(200,100);
    reason2.setCharacterSize(60);
    //skip_command.setFillColor(sf::Color::White);
    reason2.setString("No more bullets left");

    Score.setFont(arial);
    Score.setPosition(0, 10);
    Score.setCharacterSize(15);
    //Score.setString("");

    Life.setFont(arial);
    Life.setPosition(850, 10);
    Life.setCharacterSize(15);

    //level change text
    Level2.setFillColor(sf::Color::Red);
    Level2.setFont(pdark);
    Level2.setPosition(200, 550);
    Level2.setCharacterSize(40);

    //variable for rectangle shapes
    float rectPosx, rectPosy;
    rectPosx = 100;
    rectPosy = 180;


    //shapes and texts for scene 1
    sf::RectangleShape rect1, rect2, rect3, rect4;     //4 rectangular shape for the menus

    rect1.setSize(sf::Vector2f(300, 50));
    rect1.setOutlineColor(sf::Color::Black);
    rect1.setOutlineThickness(5);
    rect1.setFillColor(sf::Color::White);
    rect1.setPosition(rectPosx, rectPosy);
    sf::Text start("START", neuro);
    start.setFillColor(sf::Color::Red);
    start.setCharacterSize(45);
    start.setPosition(rectPosx + 80, rectPosy);

    rect2.setSize(sf::Vector2f(300, 50));
    rect2.setOutlineColor(sf::Color::Black);
    rect2.setOutlineThickness(5);
    rect2.setFillColor(sf::Color::White);
    rect2.setPosition(rectPosx, rectPosy + 70);
    sf::Text help("HELP", neuro);
    help.setFillColor(sf::Color::Red);
    help.setCharacterSize(40);
    help.setPosition(rectPosx + 80, rectPosy + 70);

    rect3.setSize(sf::Vector2f(300, 50));
    rect3.setOutlineColor(sf::Color::Black);
    rect3.setOutlineThickness(5);
    rect3.setPosition(rectPosx, rectPosy + 70 * 2);
    rect3.setFillColor(sf::Color::White);

    sf::Text about("ABOUT", neuro);
    about.setFillColor(sf::Color::Red);
    about.setCharacterSize(40);
    about.setPosition(rectPosx + 80, rectPosy + 140);

    rect4.setSize(sf::Vector2f(300, 50));
    rect4.setOutlineColor(sf::Color::Black);
    rect4.setOutlineThickness(5);
    rect4.setFillColor(sf::Color::White);
    rect4.setPosition(rectPosx, rectPosy + 70 * 3);
    sf::Text exit("EXIT", neuro);
    exit.setFillColor(sf::Color::Red);
    exit.setCharacterSize(40);
    exit.setPosition(rectPosx + 85, rectPosy + 210);

    sf::RectangleShape blife;
    //boss life
    int blifex = 600;
    blife.setSize(sf::Vector2f(blifex, 30));
    blife.setOutlineColor(sf::Color::Black);
    blife.setOutlineThickness(3);
    blife.setFillColor(sf::Color::Red);
    blife.setPosition(200, 10);
    sf::Text lifeb("Boss Health", neuro);
    lifeb.setFillColor(sf::Color::Blue);
    lifeb.setCharacterSize(15);
    lifeb.setPosition(450, 15);

    //variable for collision handling
    sf::Vector2f bulpos;


    //experimental: Enemy bullets
    sf::Texture ebl;
    ebl.loadFromFile("sbullet3.png");
    int jj;
    sf::Sprite ebulet[15];

    for (jj = 0; jj<15; jj++)
    {
        ebulet[jj].setTexture(ebl);
    }
    int ebullet_no = 0;

    //time handling each one is shot after a certain time
    sf::Clock enemy_b;
    sf::Time lastb;
    enemy_b.restart();


    //experiment end

    //helicopter variables
    float y_shift,h_angle=0,pi;
    pi=std::acos(-1);

    //view (scrolling)

    //adding gravity
    int gravity = 1;
    float jumpspeed = 12, velocity=0;
    int ground = tankY;   //////////////////////////////////

    //merging level 1 & 2
    int level=1;

    sf::Clock lvll2;
    sf::Time lvlchange;
    bool draw_change= true,draw_change3= true;
    int lvlebulspeedx[3] = {-4,-9,-11};
    int lvlebulspeedy[3] = {7,9,11};
    int lvlebultime[3] = {1100,600, 600};
    int lvlcngscore = 50,lvlcngscore3 = 150;


    //level3
    sf::Texture extraenemy;
    extraenemy.loadFromFile("extraenemy.png");
    sf::Sprite exenemy[5];
    for(ii=0; ii<5; ii++)
    {
        exenemy[ii].setTexture(extraenemy);
        exenemy[ii].setPosition(-5,rand()%600);
    }

    //file ops (high score)
    FILE *file;
    int scoreF;
    int score_flag;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if (scene == 2 && event.key.code == sf::Keyboard::Space)
                {
                    {
                        shoot++;
                    }
                }
            }
        }

        if (shoot == 2)
        {
            // shoot
            if(level==1)
            {
                tankpos = tank.getPosition();
                bulet[bullet_no++].setPosition(tankpos.x + 105, tankpos.y - 12);
                fire_sound.play();
                shoot = 0;  ////bullet has been already shot, resetting the vaiable
            }
            if(level==2 || level == 3)
            {
                helilv2pos = helilv2.getPosition();
                bulet[bullet_no++].setPosition(helilv2pos.x + 155, helilv2pos.y - 12);
                fire_sound.play();
                shoot = 0;  ////bullet has been already shot, resetting the vaiable
            }
        }



        elapsed = cclock.getElapsedTime();

        if (scene == 0 && elapsed.asSeconds()>start_hold)       //scene 0 will end after start_hold seconds
        {
            scene = 1;
        }

        if (scene == 0)
        {

            //control part
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                scene = 1;
                music.stop();
            }

            //drawing part
            window.clear();
            window.draw(start_scr);
            window.draw(title);
            title.move(0, -1);
            window.draw(skip_command);
            window.draw(skip_command2);
            window.display();

        }


        if (scene == 1)
        {
             int lvlcngscore = 40,lvlcngscore3 = 120;
              blifex = 600;//bossdie=0;

            //setting the title position
            title.setPosition(50, 50);
            score =0; //resetting score

            //resetting level
            level = 1;
            draw_change=true;

            //animating the explosion
            driver++;      //variable is used for animating the explosion
            if (driver>64)
            {
                driver = 0;
            }

            explo.setPosition(500, 300);
            sf::IntRect ex_rect(ex_l*driver, ex_t, ex_w, ex_h);
            explo.setTextureRect(ex_rect);


            /*control part */
            //using the mouse input for selection using live input(not events)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                localpos = sf::Mouse::getPosition(window);
                //closing window when exit is clicked
                if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 210 && localpos.y < rectPosy + 260)
                {
                    window.close();
                }
                //selecting start
                else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy && localpos.y < rectPosy + 50)
                {
                    scene = 10;
                    heli.setPosition(heliX, 100);
                }
                //selecting help
                else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 70 && localpos.y < rectPosy + 120)
                {
                    //action
                    scene = 4;

                }
                else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 140 && localpos.y < rectPosy + 190)
                {
                    //action
                    scene = 5;

                }
            }
            //setting back to regular
            rect1.setFillColor(sf::Color::White);
            rect2.setFillColor(sf::Color::White);
            rect3.setFillColor(sf::Color::White);
            rect4.setFillColor(sf::Color::White);

            //highlighting when mouse pointer is on a particular point
            localpos = sf::Mouse::getPosition();
            rectPosy+=85;
            rectPosx+=85;

            if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 210 && localpos.y < rectPosy + 260)
            {
                rect4.setFillColor(sf::Color::Yellow);
                //std::cout << localpos.y <<std::endl;
            }
            //selecting start
            else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy && localpos.y < rectPosy + 50)
            {
                rect1.setFillColor(sf::Color::Yellow);
            }
            else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 70 && localpos.y < rectPosy + 120)
            {
                rect2.setFillColor(sf::Color::Yellow);

            }
            else if (localpos.x> rectPosx + 85 && localpos.x< rectPosx + 385 && localpos.y> rectPosy + 140 && localpos.y < rectPosy + 190)
            {
                rect3.setFillColor(sf::Color::Yellow);

            }
            rectPosy-=85;
            rectPosx-=85;


            //drawing part
            window.clear();
            window.draw(background1);
            window.draw(title);
            window.draw(rect1);
            window.draw(rect2);
            window.draw(rect3);
            window.draw(rect4);
            window.draw(start);
            window.draw(help);
            window.draw(about);
            window.draw(exit);
            window.draw(explo);
            window.display();
        }

        if (scene == 2)
        {
            if(level==1)
            {
                //handing live keyboard input
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    // left key is pressed: move our character
                    tank.move(-10, 0);
                    tankpos = tank.getPosition();
                    if (tankpos.x<tankX)      //tank position fixing
                    {
                        tank.setPosition(tankX, tankY);
                    }
                    //std::cout<<tankpos.x <<std::endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    tank.move(8, 0);
                }
            }

            //changing character
            else if(level==2 || level ==3)
            {
                //handing live keyboard input
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    // left key is pressed: move our character
                    helilv2.move(-10, 0);
                    helilv2pos = helilv2.getPosition();
                    if (helilv2pos.x<helilv2X)      //tank position fixing
                    {
                        helilv2.setPosition(helilv2X, helilv2Y);
                    }
                    //std::cout<<helilv2pos.x <<std::endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    helilv2.move(8, 0);
                }
            }

            helilv2pos = helilv2.getPosition();
            if(helilv2pos.x>1100)
            {
                helilv2.setPosition(tankX,tankY);
            }


            //not using live input for shooting because its too fast instead using event handling
            if(score == lvlcngscore && draw_change)
            {

                lvll2.restart();
                lvlchange = lvll2.getElapsedTime();
                Level2.setString("You Reached Level 2");
                Level2.setPosition(200, 550);
                heli.setPosition(heliX,100);
                while(lvlchange.asMilliseconds()<2000)
                {
                    window.clear();
                    window.draw(background2);
                    window.draw(Level2);
                    Level2.move(0,-4);
                    window.display();
                    lvlchange = lvll2.getElapsedTime();
                }
                level=2;
                draw_change =false ;

            }
            if(score>lvlcngscore && score < lvlcngscore3)
            {
                draw_change=true;
                level = 2 ;
            }

            //condition for entering level 3
            if(score == lvlcngscore3 && draw_change3)
            {

                lvll2.restart();
                lvlchange = lvll2.getElapsedTime();
                Level2.setPosition(200, 550);
                Level2.setString("You reached Level 3");
                boss.setPosition(bossX,100);
                blifex=600;
                lives+=2;
                while(lvlchange.asMilliseconds()<2000)
                {
                    window.clear();
                    window.draw(back3);
                    window.draw(Level2);
                    Level2.move(0,-4);
                    window.display();
                    lvlchange = lvll2.getElapsedTime();
                }
                level=3;
                draw_change3 =false ;

            }
            if(score>lvlcngscore3)
            {
                draw_change3=true;
                level = 3 ;
            }


            if(level==2 || level ==3)
            {

                //adding gravity
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    velocity = -1 * jumpspeed;

                }

                //not using live input for shooting because its too fast instead using event handling

                //control with gravity
                helilv2.move(0, velocity);
                if (helilv2.getPosition().y < ground)
                {
                    velocity += gravity;
                }
                else
                {
                    helilv2.setPosition(helilv2.getPosition().x, helilv2Y);
                    velocity = 0;
                }

            }

            //game over conditions
            if (lives<1)
            {
                bullet_no = 0;
                lives = 3;
                scene = 3;
                over_reason = 10;
            }
            if (bullet_no>49)
            {
                bullet_no = 0;
                lives = 3;
                scene = 3;
                over_reason = 2;
            }

            helipos = heli.getPosition();
            //resetting position when helicopter is out of the window
            if (helipos.x<0 || helipos.x>1300)
            {
                heli.setPosition(heliX, 100);
                lives--;
            }

            bosspos = boss.getPosition();
            //resetting position when boss is out of the window
            if (bosspos.x<0 || bosspos.x>1300)
            {
                boss.setPosition(bossX, 100);
                lives--;
            }

            if(level==2 || level == 3)
            {

                //helicopter movement
                y_shift=std::sin(1.2*h_angle*pi/180);
                /*angle loop */
                if(h_angle>360)
                {
                    h_angle=0;
                }
                h_angle++;
                //std::cout<<y_shift <<std::endl;
            }
            else y_shift=0;
            if(level<3) heli.move(-3, y_shift);
            else boss.move(-3, y_shift);


            //collision detection for bullet and enemy(bounding box)
            temp = bullet_no-1;
            while (temp>=0)
            {
                if(level<3){
                if (bulet[temp].getGlobalBounds().intersects(heli.getGlobalBounds()))
                {
                    //std::cout << "The sprite have collided" << std::endl;
                    helipos = heli.getPosition();
                    explo.setPosition(helipos);
                    heli.setPosition(heliX+170, 100);
                    bulet[temp].setPosition(-1,-5);
                    score += 10*level;
                    explo_sound.play();

                    draw_explo = true;
                    driver = 5;
                }
                }
                else{
                         if (bulet[temp].getGlobalBounds().intersects(boss.getGlobalBounds()))
                {
                    //std::cout << "The sprite have collided" << std::endl;
                    blifex-=100;
                    blife.setSize(sf::Vector2f(blifex, 30));
                    score += 10*level;
                    bosspos = boss.getPosition();
                    explo.setPosition(bosspos);
                  //  boss.setPosition(bossX+170, 100);
                    bulet[temp].setPosition(-1,-5);

                    explo_sound.play();

                    draw_explo = true;
                    driver = 5;
                    if(blifex <0){
                        over_reason= 11;
                        scene = 3;
                        reason2.setString("             You Win!!");
                    }

                }

                }
                temp--;

            }

            if(level <3)
            {

                int etemp = 14;
                //experimental
                lastb = enemy_b.getElapsedTime();
                if (lastb.asMilliseconds()>lvlebultime[level-1])
                {
                    ebulet[ebullet_no++].setPosition(helipos.x + 60, helipos.y + 50);
                    enemy_b.restart();
                }
                if (ebullet_no>14)
                {
                    ebullet_no = 0;
                }
            }

            else if (level ==3)
            {
                int etemp = 14;
                sf::Vector2f bosspos(boss.getPosition());

                lastb = enemy_b.getElapsedTime();
                if (lastb.asMilliseconds()>lvlebultime[level-1])
                {
                    ebulet[ebullet_no++].setPosition(bosspos.x + 60, bosspos.y + 50);
                    enemy_b.restart();
                }
                if (ebullet_no>14)
                {
                    ebullet_no = 0;
                }
            }

            //enemy bullet collision with User sprite
            int etemp = 14;
            while (etemp >= 0)
            {
                if(level==1)
                {
                    if (ebulet[etemp].getGlobalBounds().intersects(tank.getGlobalBounds()))
                    {
                        //std::cout << "The sprite have collided" << std::endl;
                        //helipos = heli.getPosition();
                        tankpos = tank.getPosition();
                        explo2.setPosition(tankpos);
                        explo_sound.play();
                        tank.setPosition(1200, 900);
                        //tank.setPosition(tankX, tankY);
                        ebulet[etemp].setPosition(-2, -3);
                        lives--;
                        draw_explo2 = true;
                        driver2 = 10;
                    }
                }
                else if(level==2 || level ==3)
                {
                    if (ebulet[etemp].getGlobalBounds().intersects(helilv2.getGlobalBounds()))
                    {
                        //std::cou..\SFML-2.4.1\includet << "The sprite have collided" << std::endl;
                        //helipos = heli.getPosition();
                        helilv2pos = helilv2.getPosition();
                        explo2.setPosition(helilv2pos);
                        explo_sound.play();
                        helilv2.setPosition(1200, 900);
                        //tank.setPosition(tankX, tankY);
                        ebulet[etemp].setPosition(-2, -3);
                        lives--;
                        draw_explo2 = true;
                        driver2 = 10;
                    }

                }
                etemp--;
            }

            //animating the explosion
            if (draw_explo)
            {
                driver++;      //variable is used for animating the explosion
                if (driver>45)
                {
                    draw_explo = false;
                }
            }

            sf::IntRect ex_rect(ex_l*driver, ex_t, ex_w, ex_h);
            explo.setTextureRect(ex_rect);

            if (draw_explo2)
            {
                driver2++;      //variable is used for animating the explosion
                if (driver2>40)
                {
                    draw_explo2 = false;
                    if(level==1)
                    {
                        tank.setPosition(tankX, tankY);
                    }
                    else if(level==2)
                    {
                        helilv2.setPosition(helilv2X, helilv2Y);
                    }
                }
            }

            sf::IntRect ex_rect2(ex_l2*driver2, ex_t2, ex_w2, ex_h2);
            explo2.setTextureRect(ex_rect2);

            //std::cout << helipos.x <<" " << helipos.y <<std::endl;

            //sprite animation for helicopter
            heliD++;
            if (heliD>2)
            {
                heliD = 0;
            }
            sf::IntRect pos2(205 * heliD, 0, 205, 119);
            heli.setTextureRect(pos2);


            std::stringstream ss;
            ss << score;
            std::string scr = ss.str();
            Score.setString("Score is " + scr);

            std::stringstream sv;
            sv<<lives;
            std::string str = sv.str();
            Life.setString("Remaining lives " + str);



            /*Drawing part*/

            window.clear();
            if(level==1)
            {
                window.draw(background2);
                window.draw(tank);
            }
            else if(level==2)
            {
                window.draw(bglv2);
                window.draw(helilv2);
            }
            else if(level == 3)
            {
                window.draw(back3);
                window.draw(helilv2);
                window.draw(blife);
                window.draw(lifeb);
            }

            if(level<3) window.draw(heli);
            else window.draw(boss);
            //drawing bullet
            temp = bullet_no - 1;
            while (temp >= 0)
            {
                window.draw(bulet[temp]);
                bulet[temp--].move(3.5, -7.5);
            }

            //experiment start
            etemp = 14;
            while (etemp >= 0)
            {
                window.draw(ebulet[etemp]);
                ebulet[etemp--].move(lvlebulspeedx[level-1],lvlebulspeedy[level-1]);
            }
            //experiment end

            if (draw_explo)
            {
                window.draw(explo);
            }
            if (draw_explo2)
            {
                window.draw(explo2);
            }

            window.draw(Score);
            window.draw(Life);
            window.display();


        }

        if (scene == 3)
        {
            //control part
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                scene = 1;
            }

            file = fopen("scores.txt","r");
            fscanf(file,"%d",&scoreF);
            if(scoreF <= score)
            {
                fclose(file);
                file = fopen("scores.txt","w");
                fprintf(file,"%d",score);
                fclose(file);
            }
            else
            {
                std::stringstream ss;
                ss << scoreF;
                std::string scr = ss.str();
                Hscr.setString("Current High Score: "+scr);
                score_flag =10;
                fclose(file);

            }

            std::stringstream ss;
            ss << score;
            std::string scr = ss.str();
            High_score.setString("SCORE: "+scr);
            score_flag = 66;
            if(score_flag !=10) Hscr.setString("Current High Score: "+scr);

            //initialization
            level=1;
            lvlcngscore= 50;
            lvlcngscore3=50+20*5;
            lives=3;

            //drawing part
            window.clear();
            window.draw(bg_over);
            window.draw(skip_command);
            window.draw(skip_command2);

            if (over_reason == 10)
            {
                window.draw(reason1);
            }
            else
            {
                window.draw(reason2);
            }
            window.draw(High_score);
            window.draw(Hscr);

            window.display();
        }

        if (scene == 4)     //Help page
        {
            window.clear();
            window.draw(helpbg);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                scene = 1;
            }
        }

        if (scene == 5)     //about page
        {
            window.clear();
            window.draw(about1);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                scene = 1;
            }
        }

        if (scene == 10)     //about page
        {
            /*control part */
            //using the mouse input for selection using live input(not events)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                localpos = sf::Mouse::getPosition(window);
                //std::cout<<localpos.x <<"  " <<localpos.y<<std::endl;

                if (localpos.x> 534 && localpos.x< 725)
                {
                    if (localpos.y> 173 && localpos.y < 286)
                    {
                        scene = 2;
                        level = 1;
                    }
                    else if (localpos.y> 305 && localpos.y < 419)
                    {
                        //level = 2;
                        scene = 2;
                        lvlcngscore =0;
                        //draw_change = false;

                    }
                    else if (localpos.y> 435 && localpos.y < 548)
                    {
                        level = 3;
                        scene = 2;
                        lvlcngscore3 =0;
                        lvlcngscore =3000;

                    }
                }
            }

            window.clear();
            window.draw(lvchoice);
            window.display();

        }


    }
    return 0;
}
