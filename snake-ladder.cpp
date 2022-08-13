#include <bits/stdc++.h>

using namespace std;

enum PlayerStatus
{
    OUT,
    PLAYING,
};

enum GameStatus
{
    ACTIVE,
    OVER
};

class Board
{
    int cells;
    int dice;

public:
    map<int, int> snakes;  //[start->end]
    map<int, int> ladders; //[start->end]

    Board(int cells = 100, int dice = 1) : cells(cells), dice(dice){};
    void setSnakes(int, int);
    void setLadders(int, int);
    int rollDice();
};

void Board::setSnakes(int start, int end)
{
    snakes[start] = end;
}

void Board::setLadders(int start, int end)
{
    ladders[start] = end;
}

int Board::rollDice()
{
    int lowerBound = 1 * dice;
    int upperBound = 6 * dice;

    static bool first = true;
    if (first)
    {
        srand(time(NULL)); // seeding for the first time only!
        first = false;
    }
    int value = lowerBound + rand() % ((upperBound + 1) - lowerBound);
    return value;
}

class Player
{
    string playerName;
    int currentPosition;
    vector<pair<int, int>> moveHistory;
    PlayerStatus playerStatus;

public:
    Player(string playerName, int currentPosition = 0, PlayerStatus playerStatus = PlayerStatus::PLAYING) : playerName(playerName), currentPosition(currentPosition), playerStatus(playerStatus){};
    string getPlayerName();
    int getCurrentPosition();
    vector<pair<int, int>> getLastMoves(int);
    void setPlayerName(string);
    void setCurrentPosition(int);
    void updateHistory(int, int);
    void setPlayerStatus(PlayerStatus);
    PlayerStatus getPlayerStatus();
};

string Player::getPlayerName()
{
    return playerName;
}

void Player::setPlayerName(string playerName)
{
    this->playerName = playerName;
}

int Player::getCurrentPosition()
{
    return currentPosition;
}

void Player::setCurrentPosition(int currentPosition)
{
    this->currentPosition = currentPosition;
}

/**
 * Get last N moves
 * @param N last N moves
 * @return vector<pair<int,int>> moves; {position,dice roll}
 *
 */
vector<pair<int, int>> Player::getLastMoves(int N)
{

    vector<pair<int, int>> lastNMoves;
    int totalMoves = moveHistory.size() - 1;
    int iterator = totalMoves - 1;
    while (iterator >= 0 && N--)
    {
        lastNMoves.push_back(moveHistory[iterator--]);
    }

    return lastNMoves;
}

void Player::updateHistory(int currentPosition, int diceValue)
{
    this->moveHistory.push_back({currentPosition, diceValue});
}

void Player::setPlayerStatus(PlayerStatus playerStatus)
{
    this->playerStatus = playerStatus;
}

PlayerStatus Player::getPlayerStatus()
{
    return this->playerStatus;
}

class Game
{
    int totalPlayers;
    queue<Player> players;
    GameStatus gameStatus;
    vector<Player> playerRanks;
    Board board;

public:
    Game(Board &board, int totalPlayer = 0, GameStatus gameStatus = GameStatus::ACTIVE) : board(board), totalPlayers(totalPlayers), gameStatus(gameStatus){};
    void addPlayers(Player);
    void setGameStatus(GameStatus);
    GameStatus getGameStatus();
    void updatePlayerRank(Player);
    vector<Player> getActivePlayers();
    void makeMove();
    void endGame();
};

void Game::addPlayers(Player player)
{
    this->players.push(player);
}

void Game::setGameStatus(GameStatus gameStatus)
{
    this->gameStatus = gameStatus;
}

GameStatus Game::getGameStatus()
{
    return this->gameStatus;
}

void Game::updatePlayerRank(Player player)
{
    player.setPlayerStatus(PlayerStatus::OUT);
    this->playerRanks.push_back(player);
}

vector<Player> Game::getActivePlayers()
{
    queue<Player> activePlayers = players;

    vector<Player> playerList;

    while (!activePlayers.empty())
    {
        Player player = activePlayers.front();
        activePlayers.pop();
        playerList.push_back(player);
    }

    return playerList;
}

void Game::makeMove()
{
    if (gameStatus == GameStatus::OVER)
    {
        cout << "Game is not active" << endl;
        return;
    }
    Player currentPlayer = players.front();
    players.pop();

    int diceValue = board.rollDice();
    int currentPosition = currentPlayer.getCurrentPosition();

    if (currentPosition + diceValue <= 100)
    {
        int finalPosition = currentPosition + diceValue;

        if (board.snakes.find(finalPosition) != board.snakes.end())
        {
            finalPosition = board.snakes[finalPosition];
        }
        else if (board.ladders.find(finalPosition) != board.ladders.end())
        {
            finalPosition = board.ladders[finalPosition];
        }
        currentPlayer.setCurrentPosition(finalPosition);
        currentPlayer.updateHistory(currentPosition, diceValue);
        cout << currentPlayer.getPlayerName() << " rolled a " << diceValue << " and moved from " << currentPosition << " to " << finalPosition << endl;

        if (finalPosition == 100)
        {
            currentPlayer.setPlayerStatus(PlayerStatus::OUT);
            this->updatePlayerRank(currentPlayer);

            if (players.size() == 1)
            {
                this->updatePlayerRank(players.front());
                players.pop();
                this->endGame();
            }
        }
        else
        {
            players.push(currentPlayer);
        }
    }
    else
    {
        cout << currentPlayer.getPlayerName() << " rolled a " << diceValue << " and moved from " << currentPosition << " to " << currentPosition << endl;
        players.push(currentPlayer);
    }
}

void Game::endGame()
{
    if (gameStatus == GameStatus::ACTIVE)
    {
        setGameStatus(GameStatus::OVER);
        cout << endl;
        cout << endl;
        cout << "=======GAME OVER=======" << endl;
        int rank = 1;
        for (auto player : playerRanks)
        {
            cout << rank << ". " << player.getPlayerName() << endl;
            rank++;
        }
        return;
    }
    else
    {
        cout << "Game has already ended";
    }
}

int main()
{
    cout << "============WELCOME TO SNAKE AND LADDER GAME==========" << endl;

    Board board(100, 1);

    int snakes;
    cin >> snakes;

    while (snakes--)
    {
        int start, end;
        cin >> start >> end;
        board.setSnakes(start, end);
    }

    int ladders;
    cin >> ladders;

    while (ladders--)
    {
        int start, end;
        cin >> start >> end;
        board.setLadders(start, end);
    }

    int players;
    cin >> players;
    Game game(board, players);

    while (players--)
    {
        string name;
        cin >> name;
        Player player(name);
        game.addPlayers(player);
    }
    cout << endl;
    cout << endl;
    while (game.getGameStatus() == GameStatus::ACTIVE)
        game.makeMove();

    return 0;
}