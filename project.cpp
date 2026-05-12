#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
#include "Enemy.h"
#include "BasicEnemy.h"
#include "FastEnemy.h"
#include "TankEnemy.h"
#include "FlyingEnemy.h"
#include "HealerEnemy.h"
#include "Tower.h"
#include "CannonTower.h"
#include "SniperTower.h"
#include "MachineGunTower.h"
#include "SlowTower.h"
bool check_path(Vector2f clickPos, RectangleShape segs[], int seg_count, float margin = 10.f) {
    for (int i = 0; i < seg_count; i++) {
        FloatRect bounds = segs[i].getGlobalBounds();
        bounds.left -= margin;
        bounds.top -= margin;
        bounds.width += margin * 2;
        bounds.height += margin * 2;
        if (bounds.contains(clickPos))
            return true;
    }
    return false;
}

void rescaleMap(Sprite& mapSprite, Texture& mapTexture, float w, float h) {
    mapSprite.setScale(
        w / mapTexture.getSize().x,
        h / mapTexture.getSize().y
    );
}

void buildPath(RectangleShape segs[], Vector2f waypoints[], float w, float h, float t, Color pathColor) {
    waypoints[0] = { w * 0.12f, 0.f };
    waypoints[1] = { w * 0.12f, h * 0.28f };
    waypoints[2] = { w * 0.70f, h * 0.28f };
    waypoints[3] = { w * 0.70f, h * 0.48f };
    waypoints[4] = { w * 0.27f, h * 0.48f };
    waypoints[5] = { w * 0.27f, h * 0.72f };
    waypoints[6] = { w * 0.85f, h * 0.72f };
    waypoints[7] = { w * 0.85f, h };

    segs[0].setSize({ t, waypoints[1].y - waypoints[0].y + t / 2.f });
    segs[0].setPosition(waypoints[0].x - t / 2.f, 0.f);
    segs[0].setFillColor(pathColor);

    segs[1].setSize({ waypoints[2].x - waypoints[1].x + t, t });
    segs[1].setPosition(waypoints[1].x - t / 2.f, waypoints[1].y - t / 2.f);
    segs[1].setFillColor(pathColor);

    segs[2].setSize({ t, waypoints[3].y - waypoints[2].y + t });
    segs[2].setPosition(waypoints[2].x - t / 2.f, waypoints[2].y - t / 2.f);
    segs[2].setFillColor(pathColor);

    segs[3].setSize({ waypoints[3].x - waypoints[4].x + t, t });
    segs[3].setPosition(waypoints[4].x - t / 2.f, waypoints[3].y - t / 2.f);
    segs[3].setFillColor(pathColor);

    segs[4].setSize({ t, waypoints[5].y - waypoints[4].y + t });
    segs[4].setPosition(waypoints[4].x - t / 2.f, waypoints[4].y - t / 2.f);
    segs[4].setFillColor(pathColor);

    segs[5].setSize({ waypoints[6].x - waypoints[5].x + t, t });
    segs[5].setPosition(waypoints[5].x - t / 2.f, waypoints[5].y - t / 2.f);
    segs[5].setFillColor(pathColor);

    segs[6].setSize({ t, h - waypoints[6].y });
    segs[6].setPosition(waypoints[6].x - t / 2.f, waypoints[6].y - t / 2.f);
    segs[6].setFillColor(pathColor);
}

const int wave_count = 5;
const int max_in_wave = 12;
int waveData[wave_count][max_in_wave] = {
    { 0, 0, 0, 0, 0,  0,  0, -1, -1, -1, -1, -1 },
    { 0, 0, 1, 1, 1,  1,  1,  1, -1, -1, -1, -1 },
    { 1, 1, 1, 1, 2,  2,  2, -1, -1, -1, -1, -1 },
    { 2, 2, 2, 2, 4,  4,  4,  1,  1,  1, -1, -1 },
    { 0, 1, 2, 3, 4,  0,  1,  2,  3,  4,  2,  1 }
};
int wave_size[wave_count] = { 7, 8, 7, 10, 12 };

int main() {
    VideoMode desktop = VideoMode::getDesktopMode();
    RenderWindow window(desktop, "Tower Defense", Style::Default);
    window.setFramerateLimit(60);
    Clock clock;
    Music bgMusic;

    if (!bgMusic.openFromFile("audio.mp3")) {
        cout << "Failed to load music" << endl;
    }
    bgMusic.setLoop(true);
    bgMusic.setVolume(40.f);
    bgMusic.play();

    float w = (float)desktop.width;
    float h = (float)desktop.height;

    Font font;
    if (!font.loadFromFile("font.ttf"))
        cout << "Failed to load font" << endl;

    Texture mapTexture;
    Sprite mapSprite;
    if (!mapTexture.loadFromFile("grass_5.png"))
        cout << "Failed to load map" << endl;
    mapSprite.setTexture(mapTexture);
    rescaleMap(mapSprite, mapTexture, w, h);

    float t = 100.f;
    Color pathColor(139, 90, 43);
    RectangleShape segs[7];
    Vector2f waypoints[8];
    buildPath(segs, waypoints, w, h, t, pathColor);

    CircleShape entryMarker(14.f);
    entryMarker.setFillColor(Color(0, 200, 0));
    entryMarker.setOrigin(14.f, 14.f);
    entryMarker.setPosition(waypoints[0]);

    CircleShape exitMarker(14.f);
    exitMarker.setFillColor(Color(200, 0, 0));
    exitMarker.setOrigin(14.f, 14.f);
    exitMarker.setPosition(waypoints[7]);

    float bar_height = 130.f;
    RectangleShape bottom_bar;
    bottom_bar.setSize({ w, bar_height });
    bottom_bar.setPosition(0.f, h - bar_height);
    bottom_bar.setFillColor(Color(30, 30, 30, 220));

    Texture cannon_t, sniper_t, mg_t, slow_t;
    cannon_t.loadFromFile("cannon_tower.png");
    sniper_t.loadFromFile("sniper_tower.png");
    mg_t.loadFromFile("machine_tower.png");
    slow_t.loadFromFile("slow_tower2.png");

    const int tower_types = 4;
    RectangleShape towerbuttons[tower_types];
    Sprite towerbuttonsprites[tower_types];
    Texture* towerbuttontextures[tower_types] = { &cannon_t, &sniper_t, &mg_t, &slow_t };
    string towernames[tower_types] = { "Cannon", "Sniper", "MachineGun", "Slow" };
    int towercosts[tower_types] = { 100, 125, 90, 80 };
    Color towercolors[tower_types] = {
        Color(180, 80,  80),
        Color(80,  80,  180),
        Color(80,  180, 80),
        Color(180, 180, 80)
    };

    float buttonsize = 80.f;
    float buttonpad = 20.f;
    float buttonStartX = (w - (tower_types * (buttonsize + buttonpad))) / 2.f;
    float buttonY = h - bar_height + 10.f;

    for (int i = 0; i < tower_types; i++) {
        towerbuttons[i].setSize({ buttonsize, buttonsize });
        towerbuttons[i].setPosition(buttonStartX + i * (buttonsize + buttonpad), buttonY);
        towerbuttons[i].setFillColor(towercolors[i]);
        towerbuttons[i].setOutlineThickness(2.f);
        towerbuttons[i].setOutlineColor(Color::White);

        towerbuttonsprites[i].setTexture(*towerbuttontextures[i]);
        float scl = buttonsize / (float)max(towerbuttontextures[i]->getSize().x, towerbuttontextures[i]->getSize().y);
        towerbuttonsprites[i].setScale(scl, scl);
        towerbuttonsprites[i].setPosition(buttonStartX + i * (buttonsize + buttonpad), buttonY);
    }

    Text costlabels[tower_types];
    Text namelabels[tower_types];
    for (int i = 0; i < tower_types; i++) {
        namelabels[i].setFont(font);
        namelabels[i].setCharacterSize(13);
        namelabels[i].setFillColor(Color::White);
        namelabels[i].setString(towernames[i]);
        namelabels[i].setPosition(buttonStartX + i * (buttonsize + buttonpad),
            buttonY + buttonsize + 2.f);

        costlabels[i].setFont(font);
        costlabels[i].setCharacterSize(13);
        costlabels[i].setFillColor(Color::Yellow);
        costlabels[i].setString(to_string(towercosts[i]) + "g");
        costlabels[i].setPosition(buttonStartX + i * (buttonsize + buttonpad), buttonY + buttonsize + 18.f);
    }

    RectangleShape topBar;
    topBar.setSize({ w, 40.f });
    topBar.setPosition(0.f, 0.f);
    topBar.setFillColor(Color(20, 20, 20, 200));

    Text waveText, goldText, livesText;
    waveText.setFont(font);
    waveText.setCharacterSize(22);
    waveText.setFillColor(Color::White);
    waveText.setPosition(20.f, 8.f);

    goldText.setFont(font);
    goldText.setCharacterSize(22);
    goldText.setFillColor(Color::Yellow);
    goldText.setPosition(w / 2.f - 80.f, 8.f);

    livesText.setFont(font);
    livesText.setCharacterSize(22);
    livesText.setFillColor(Color::Red);
    livesText.setPosition(w - 160.f, 8.f);

    CircleShape ghostRange;
    RectangleShape ghostBody(Vector2f(50.f, 50.f));
    ghostBody.setOrigin(25.f, 25.f);
    ghostBody.setOutlineColor(Color::White);
    ghostBody.setOutlineThickness(2.f);

    int gold = 200;
    int lives = 5;
    int selectedTower = -1;
    bool gameover = false;
    bool gamewon = false;

    const int max_enemies = 100;
    Enemy* enemies[max_enemies];
    int enemy_count = 0;
    for (int i = 0; i < max_enemies; i++) enemies[i] = nullptr;

    int currentwave = 0;
    int spawnindex = 0;
    float spawntimer = 0.f;
    float spawninterval = 1.5f;
    bool  waveactive = true;

    const int max_towers = 50;
    Tower* towers[max_towers];
    int tower_count = 0;
    for (int i = 0; i < max_towers; i++) towers[i] = nullptr;

    RectangleShape overlay;
    overlay.setSize({ w, h });
    overlay.setFillColor(Color(0, 0, 0, 160));

    Text bigtext;
    bigtext.setFont(font);
    bigtext.setCharacterSize(72);

    Text subtext;
    subtext.setFont(font);
    subtext.setCharacterSize(30);
    subtext.setFillColor(Color(200, 200, 200));
    subtext.setString("Press ESC to quit");

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        Vector2i mouse_pos = Mouse::getPosition(window);
        Vector2f mousePosF((float)mouse_pos.x, (float)mouse_pos.y);

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();

            if (event.type == Event::MouseButtonPressed) {
                Vector2f click((float)event.mouseButton.x,
                    (float)event.mouseButton.y);

                if (event.mouseButton.button == Mouse::Right)
                    selectedTower = -1;

                if (event.mouseButton.button == Mouse::Left) {
                    for (int i = 0; i < tower_types; i++) {
                        if (towerbuttons[i].getGlobalBounds().contains(click)) {
                            if (selectedTower == i)
                                selectedTower = -1;
                            else
                                selectedTower = i;
                            break;
                        }
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                Vector2f click((float)event.mouseButton.x,
                    (float)event.mouseButton.y);

                if (event.mouseButton.button == Mouse::Left &&
                    selectedTower != -1 && !gameover && !gamewon) {

                    bool onPath = check_path(click, segs, 7);
                    bool onBar = (click.y > h - bar_height);
                    bool onButton = false;

                    for (int i = 0; i < tower_types; i++) {
                        if (towerbuttons[i].getGlobalBounds().contains(click)) {
                            onButton = true;
                            break;
                        }
                    }

                    if (!onPath && !onBar && !onButton) {
                        int cost = towercosts[selectedTower];
                        if (gold >= cost && tower_count < max_towers) {
                            Tower* newTower = nullptr;
                            if (selectedTower == 0) newTower = new CannonTower(click);
                            else if (selectedTower == 1) newTower = new SniperTower(click);
                            else if (selectedTower == 2) newTower = new MachineGunTower(click);
                            else if (selectedTower == 3) newTower = new SlowTower(click);

                            if (newTower) {
                                towers[tower_count] = newTower;
                                tower_count++;
                                gold -= cost;
                                selectedTower = -1;
                            }
                        }
                        else {
                            cout << "Not enough gold!" << endl;
                        }
                    }
                }
            }
        }

        if (!gameover && !gamewon) {
            if (waveactive && currentwave < wave_count) {
                spawntimer += dt;
                if (spawntimer >= spawninterval &&
                    spawnindex < wave_size[currentwave]) {
                    spawntimer = 0.f;
                    Vector2f spawnpos = waypoints[0];
                    spawnpos.y -= spawnindex * 60.f;

                    int type = waveData[currentwave][spawnindex];
                    Enemy* e = nullptr;
                    if (type == 0) e = new BasicEnemy(spawnpos);
                    else if (type == 1) e = new FastEnemy(spawnpos);
                    else if (type == 2) e = new TankEnemy(spawnpos);
                    else if (type == 3) e = new FlyingEnemy(spawnpos);
                    else if (type == 4) e = new HealerEnemy(spawnpos);

                    if (e && enemy_count < max_enemies) {
                        e->set_path(waypoints, 8);
                        enemies[enemy_count] = e;
                        enemy_count++;
                    }
                    spawnindex++;
                }
            }

            if (waveactive && spawnindex >= wave_size[currentwave]) {
                bool alldead = true;
                for (int i = 0; i < enemy_count; i++) {
                    if (enemies[i] && enemies[i]->get_alive()) {
                        alldead = false;
                        break;
                    }
                }

                if (alldead) {
                    for (int i = 0; i < enemy_count; i++) {
                        delete enemies[i];
                        enemies[i] = nullptr;
                    }
                    enemy_count = 0;
                    currentwave++;
                    spawnindex = 0;
                    spawntimer = 0.f;

                    if (currentwave >= wave_count)
                        gamewon = true;
                    else
                        cout << "Wave " << currentwave + 1 << " starting!" << endl;
                }
            }

            for (int i = 0; i < enemy_count; i++) {
                if (!enemies[i] || !enemies[i]->get_alive()) continue;
                enemies[i]->update(dt);
            }

            for (int i = 0; i < enemy_count; i++) {
                if (!enemies[i]) continue;
                HealerEnemy* h = dynamic_cast<HealerEnemy*>(enemies[i]);
                if (h && h->get_alive())
                    h->healNearby(enemies, enemy_count, dt);
            }

            for (int i = 0; i < enemy_count; i++) {
                if (!enemies[i]) continue;
                if (!enemies[i]->get_alive()) {
                    FlyingEnemy* flyer = dynamic_cast<FlyingEnemy*>(enemies[i]);
                    bool escaped = false;

                    if (flyer) {
                        Vector2f diff = enemies[i]->getpos() - waypoints[7];
                        float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
                        if (dist < 80.f)
                            escaped = true;
                    }
                    else {
                        if (enemies[i]->getWaypointindex() >= 8)
                            escaped = true;
                    }

                    if (escaped) {
                        lives -= enemies[i]->get_damage();
                        if (lives <= 0) {
                            lives = 0;
                            gameover = true;
                        }
                    }
                    else {
                        gold += enemies[i]->get_reward();
                    }
                    delete enemies[i];
                    enemies[i] = nullptr;
                }
            }

            for (int i = 0; i < tower_count; i++) {
                if (!towers[i]) continue;
                SlowTower* slow = dynamic_cast<SlowTower*>(towers[i]);
                CannonTower* cannon = dynamic_cast<CannonTower*>(towers[i]);
                MachineGunTower* mg = dynamic_cast<MachineGunTower*>(towers[i]);
                SniperTower* sniper = dynamic_cast<SniperTower*>(towers[i]);

                if (slow)
                    slow->update(dt, enemies, enemy_count);
                else if (cannon)
                    cannon->update(dt, enemies, enemy_count);
                else if (mg)
                    mg->update(dt, enemies, enemy_count);
                else if (sniper)
                    sniper->update(dt, enemies, enemy_count);
                else
                    towers[i]->update(dt, enemies, enemy_count);
            }
        }

        waveText.setString("Wave: " + to_string(min(currentwave + 1, wave_count))
            + " / " + to_string(wave_count));
        goldText.setString("Gold: " + to_string(gold) + "g");
        livesText.setString("Lives: " + to_string(lives));

        for (int i = 0; i < tower_types; i++) {
            if (i == selectedTower)
                towerbuttons[i].setOutlineColor(Color::Cyan);
            else
                towerbuttons[i].setOutlineColor(Color::White);
        }

        if (selectedTower != -1) {
            float previewRange = 0.f;
            if (selectedTower == 0) previewRange = 150.f;
            else if (selectedTower == 1) previewRange = 350.f;
            else if (selectedTower == 2) previewRange = 130.f;
            else if (selectedTower == 3) previewRange = 120.f;

            ghostRange.setRadius(previewRange);
            ghostRange.setOrigin(previewRange, previewRange);
            ghostRange.setPosition(mousePosF);
            ghostRange.setFillColor(Color(255, 255, 255, 20));
            ghostRange.setOutlineColor(Color(255, 255, 255, 80));
            ghostRange.setOutlineThickness(1.f);
            ghostBody.setPosition(mousePosF);

            bool invalidPos = check_path(mousePosF, segs, 7) ||
                mousePosF.y > h - bar_height ||
                gold < towercosts[selectedTower];

            if (invalidPos)
                ghostBody.setFillColor(Color(255, 80, 80, 120));
            else
                ghostBody.setFillColor(Color(255, 255, 255, 80));
        }

        window.clear(Color(30, 30, 30));
        window.draw(mapSprite);

        for (int i = 0; i < 7; i++)
            window.draw(segs[i]);

        window.draw(entryMarker);
        window.draw(exitMarker);

        for (int i = 0; i < tower_count; i++)
            if (towers[i]) towers[i]->render(window);

        for (int i = 0; i < enemy_count; i++)
            if (enemies[i] && enemies[i]->get_alive())
                enemies[i]->render(window);

        if (selectedTower != -1 && !gameover && !gamewon) {
            window.draw(ghostRange);
            window.draw(ghostBody);
        }

        window.draw(topBar);
        window.draw(waveText);
        window.draw(goldText);
        window.draw(livesText);

        window.draw(bottom_bar);
        for (int i = 0; i < tower_types; i++) {
            window.draw(towerbuttons[i]);
            window.draw(towerbuttonsprites[i]);
            window.draw(namelabels[i]);
            window.draw(costlabels[i]);
        }

        if (gameover || gamewon) {
            window.draw(overlay);
            if (gameover) {
                bigtext.setString("GAME OVER");
                bigtext.setFillColor(Color::Red);
            }
            else {
                bigtext.setString("YOU WIN!");
                bigtext.setFillColor(Color::Green);
            }
            bigtext.setOrigin(bigtext.getLocalBounds().width / 2.f,
                bigtext.getLocalBounds().height / 2.f);
            bigtext.setPosition(w / 2.f, h / 2.f - 60.f);
            subtext.setOrigin(subtext.getLocalBounds().width / 2.f, subtext.getLocalBounds().height / 2.f);
            subtext.setPosition(w / 2.f, h / 2.f + 40.f);
            window.draw(bigtext);
            window.draw(subtext);
        }
        window.display();
    }
    for (int i = 0; i < enemy_count; i++) {
        delete enemies[i];
        enemies[i] = nullptr;
    }
    for (int i = 0; i < tower_count; i++) {
        delete towers[i];
        towers[i] = nullptr;
    }
    return 0;
}