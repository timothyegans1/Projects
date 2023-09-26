#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class Fighter {
public:
    string name;
    int health;
    vector<string> moves;

    Fighter(string n) : name(n), health(100), moves({ "punch", "kick", "special move" }) {}

    string getMove(int choice) {
        return moves[choice];
    }

    void takeDamage(int dmg) {
        health -= dmg;
    }

    bool isAlive() {
        return health > 0;
    }
};

class Opponent : public Fighter {
public:
    string description;

    Opponent(string n, string desc, vector<string> moveSet = {})
        : Fighter(n), description(desc) {
        if (moveSet.empty()) {
            moves = { "enemy punch", "enemy kick", "enemy special move" };
        }
        else {
            moves = moveSet;
        }
    }

    string randomMove() {
        int randIndex = rand() % moves.size();
        return moves[randIndex];
    }
};

/*
void printWrapped(const string& text, int width) {
    int currentIndex = 0;
    while (currentIndex < text.size()) {
        int lastSpace = currentIndex + width;
        if (lastSpace >= text.size()) lastSpace = text.size() - 1;
        else while (lastSpace > currentIndex && text[lastSpace] != ' ') lastSpace--;

        cout << text.substr(currentIndex, lastSpace - currentIndex + 1) << endl;
        currentIndex = lastSpace + 1;
    }
}
*/

void combat(Fighter& player, Opponent& opponent) {
    while (player.isAlive() && opponent.isAlive()) {
        cout << "\nYour Moves:\n";
        for (size_t i = 0; i < player.moves.size(); ++i) {
            cout << i + 1 << ". " << player.moves[i] << endl;
        }

        int moveChoice;
        do {
            cout << "Choose your move (enter the number 1-3): ";
            cin >> moveChoice;
        } while (moveChoice < 1 || moveChoice > 3);

        string playerMove = player.getMove(moveChoice - 1);
        string opponentMove = opponent.randomMove();

        if (moveChoice == 3) {
            opponent.takeDamage(25);
        }
        else {
            opponent.takeDamage(15);
        }

        if (opponentMove == "Shin Shoryuken") {
            player.takeDamage(60);
        }
        else if (opponentMove == "enemy special move") {
            player.takeDamage(25);
        }
        else {
            player.takeDamage(15);
        }

        cout << "\nYou used " << playerMove << "!" << endl;
        cout << "Opponent used " << opponentMove << "!" << endl;
        cout << "\nYour health: " << player.health << " | Opponent's health: " << opponent.health << endl;
    }
}

void dialogueWithMaster(Fighter& player) {
    cout << "\nMaster: You're proving to be quite the formidable fighter!\n";
    cout << "1. Thanks, Master! I'm doing my best.\n";
    cout << "2. I'm growing weary. These fights take a toll on me.\n";
    cout << "3. I won't let our realm down.\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Master: Keep up the spirit, and remember your training.\n";
        break;
    case 2:
        cout << "Master: Rest and recover. Remember, the fate of our realm is in your hands.\n";
        player.health += 15;
        cout << "Your health has been boosted to " << player.health << "!\n";
        break;
    case 3:
        cout << "Master: That's the spirit! Show them the strength of our realm!\n";
        break;
    }
}

void dialogueWithFinalOpponent(Opponent& finalOpponent) {
    cout << "\nFinal Opponent: So, you're the one who thinks they can stop the Chaos Realm's dominance?\n";
    cout << "1. I will do everything in my power to defend my realm.\n";
    cout << "2. You don't scare me.\n";
    cout << "3. Let's just get this over with.\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Final Opponent: Noble intentions. But they won't save you.\n";
        break;
    case 2:
        cout << "Final Opponent: Bold words. I'll enjoy making you eat them.\n";
        finalOpponent.health += 10;
        break;
    case 3:
        cout << "Final Opponent: Very well. Prepare to meet your doom.\n";
        finalOpponent.health -= 10;
        break;
    }
}

void newGame() {
    string playerName;
    cout << "\nEnter your fighter's name: ";
    cin >> playerName;

    Fighter player(playerName);

    vector<Opponent> opponents = {
        Opponent("Biraka", "Once a revered champion among his kin, Biraka was hailed for his valor and unmatched combat skills. However, his fate took a tragic turn on a quest to retrieve the fabled 'Star of Luthar' from the Cursed Caverns. Unknown to him, the cavern was protected by ancient spirits that unleashed a dormant virus upon intruders. As the virus coursed through Biraka's veins, it slowly began transforming him. His once clear and strategic mind was overtaken by an insatiable rage, making him even more formidable in the arena. This feral state heightened his aggression and reflexes, turning him into an unstoppable force. Yet, there's a toll. The very virus granting him these overwhelming combat abilities is also his doom, progressively weakening his life essence. As the days pass, Biraka is painfully aware that the beast within him grows stronger, while the time he has left diminishes. Now, as the Realm Defender Tournament beckons, Biraka enters not just for glory, but in hope of finding a cure or meeting a swift end before he loses himself completely to the virus."),
        Opponent("Jeb", "Jeb, often dismissed by many as the town's resident drunkard, is a familiar sight at the gas station around the corner. With a slouched posture and a can of cheap booze never too far from reach, he's been the subject of countless local stories and jokes. But beneath this inebriated exterior lies a seasoned fighter with unmatched brawling skills. It's whispered that his penchant for alcohol dulls pain and heightens his unpredictable fighting style. Now, lured by the promise of the Realm Defender Tournament and perhaps the chance to prove his detractors wrong, Jeb steps into the arena, ready to let his fists do the talking."),
        Opponent("V", "V, once bound by chains of servitude to the mega-corporations of Night City, has since shattered those shackles. Driven by a relentless will to reclaim their destiny and a fierce disdain for those who once controlled them, V navigated the treacherous urban jungle. With each challenge, from the grimy back alleys to the luminous neon-lit rooftops, V's legend grew. Harnessing advanced tech, sheer grit, and razor-sharp instincts, they emerged as one of Night City's most formidable figures. Now, as whispers of their reputation extend beyond the city limits, V enters the Realm Defender Tournament. Not for realm dominance or personal gain, but to prove that even in a world of gods and monsters, a human spirit, once awakened, can be the most powerful force of all.."),
        Opponent("Syu", "Syu, is a stoic and disciplined warrior who has dedicated his life to the martial arts. From a young age, Syu trained in secluded dojos under various master martial artists, tirelessly seeking the true path of the warrior. His powerful and precise fighting style, marked by sharp strikes and fluid movements, soon became legendary. Constantly battling his inner demons and the dark hadou threatening to overtake him, Syu traverses different realms, challenging formidable fighters to refine his skills and understand the true essence of combat. Without a thirst for domination or power, Syu joins the Realm Defender Tournament to measure his abilities against the finest and to thwart the potential disaster a Chaos Realm victory might unleash.."),
        Opponent("Chao Kin", "Chao Kin, the son of the legendary fighter Sao Ghan, has ambitions to conquer our realm and continue his father's formidable legacy. Born in the tumultuous Chaos Realm, Chao Kin was trained from a young age by Sao Ghan, absorbing not only his father's unmatched combat techniques but also his insatiable thirst for power. Rising through the ranks with a combination of raw talent and ruthless strategy, Chao Kin soon earned the title of The Champion of the Chaos Realm. His skills are unparalleled, and he remains undefeated in combat. Driven by both a desire to honor his father's name and a vision of a new world order, Chao Kin now sets his sights on our realm, aiming to bring it under the dominion of the Chaos Realm..")
    };

    /*
    for (const auto& opponent : opponents) {
        cout << opponent.name << ":\n";
        printWrapped(opponent.description, 30);  // adjust 80 as per your desired line width
        cout << "\n";  // Separate opponents by a newline for clarity
    }
    */

    for (int i = 0; i < opponents.size(); i++) {
        Opponent& currentOpponent = opponents[i];

        cout << "\nYour opponent is " << currentOpponent.name << "! " << currentOpponent.description << endl;
        cout << "\nStarting Health: \nYour health: " << player.health << " | " << currentOpponent.name << "'s health: " << currentOpponent.health << "\n";

        combat(player, currentOpponent);

        if (!player.isAlive()) {
            cout << "\nYou were defeated by " << currentOpponent.name << ". Our realm's last hope is extinguished." << endl;
            break;
        }
        else {
            cout << "\nCongratulations! You have defeated " << currentOpponent.name << "." << endl;

            if (i == 0) {
                dialogueWithMaster(player);
                player.health = 100;  // reset player's health
            }

            if (i == 3) {
                dialogueWithFinalOpponent(currentOpponent);
            }

            if (i < opponents.size() - 1) {
                player.health = 100;  // reset player's health after each fight except the last one
            }
        }
    }

    if (player.isAlive() && opponents.back().isAlive() == false) {
        cout << "\nCongratulations! You have successfully defended our realm from the invaders of the Chaos Realm." << endl;
    }
}

int main() {
    cout << "Welcome to the Realm Defender Tournament!\n\n";
    cout << "The Chaos Realm has been victorious in 9 out of the last 10 tournaments. Legend speaks of an ancient rule, set by the Realm Gods: If a realm wins 10 tournaments in a row, they gain the permission to invade and conquer another realm of their choosing. Our realm is on the brink. If the Chaos Realm claims victory this time, our home will be lost forever.\n\n";

    char choice;
    cout << "Will you defend our realm and enter the tournament? (y/n): ";
    cin >> choice;

    if (choice == 'n' || choice == 'N') {
        cout << "You've chosen not to participate. The realm's fate is sealed. The Chaos Realm reigns supreme.\n";
        return 0;
    }

    do {
        newGame();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

