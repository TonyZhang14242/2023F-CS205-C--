#pragma once

#include <initializer_list>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
template <typename T>
void shuffle_stack(std::stack<T> &stack)
{
    std::vector<T> tmp;
    while (!stack.empty())
    {
        tmp.push_back(stack.top());
        stack.pop();
    }

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(tmp.begin(), tmp.end(), rng);

    for (const auto &cardPtr : tmp)
    {
        stack.push(cardPtr);
    }
}

template <typename T>
std::string stack_to_string(const std::stack<T> &stack)
{
    std::string result = "[";
    auto cpy = stack;
    while (!cpy.empty())
    {
        result += cpy.top()->to_string();
        cpy.pop();
        if (!cpy.empty())
        {
            result += ", ";
        }
    }
    return result + "]";
}

template <typename T>
std::string vector_to_string(const std::vector<T> &vec)
{
    std::string result = "[";
    auto cpy = vec;
    for (int i = 0; i < vec.size(); i++)
    {
        result += vec[i]->to_string();
        if (i != vec.size() - 1)
        {
            result += ", ";
        }
    }
    return result + "]";
}

namespace uno
{
    class Game;
    class Player;
    // class NumberCard;
    class Card
    {
    protected:
        /**
         * @brief The color of the card
         */
        std::string color;

    public:
        /**
         * @brief Gets the string representation of the card
         * @return The formatted string
         */
        virtual std::string to_string() const = 0;

        /**
         * @brief Gets the point of the card
         * @return The point
         */
        virtual const int get_point() const = 0;

        /**
         * @brief Gets the color of the card
         * @return The color
         */
        const std::string &get_color() const
        {
            return color;
        }

        /**
         * @brief Checks if the card can be played
         * @param game The game instance
         * @return true if the card can be played, false otherwise
         */
        virtual bool is_available(const Game &game) const = 0;

        /**
         * @brief Performs the effect of the card
         * @param game The game instance
         */
        virtual void effect(Game &game) const = 0;
    };

    class Player
    {
    private:
        /**
         * @brief The name of the player
         */
        std::string name;

        /**
         * @brief The cards in the player's hand
         */
        std::vector<const Card *> hand;

    public:
        /**
         * @brief Creates a new player with the given name
         * @param name The name of the player
         */
        explicit Player(std::string name) : name(std::move(name)) {}
        std::vector<const Card *> &getHand()
        {
            return hand;
        }
        std::string& getPlayerName(){
            return name;
        }
    };

    class Game
    {
    private:
        /**
         * The players in the game
         */
        std::vector<Player *> players;

        /**
         * The index of the current player
         */
        int current_player_index;

        /**
         * The direction of the game, 1 for right, -1 for left
         */
        int direction = 1;

        /**
         * The draw pile. Initially holds all 50 cards
         */
        std::stack<const Card *> draw;

        /**
         * The discard pile. Initially empty
         */
        std::stack<const Card *> discard;

    public:
        /**
         * @brief Creates a new game with the given players joining
         * @param players The players in the game, length must be between 2 and 4 (inclusive)
         * @throws std::invalid_argument if the number of players is invalid
         * @note For the {@param players} as {@code {"P1", "P2", "P3", "P4"}}, they should sit in the order of:
         *       ```
         *        P1  --→  P2
         *         ↖︎       ↘︎
         *          P4  ←--  P3
         *       ```
         */
        Game(std::initializer_list<Player *> players);

        /**
         * @brief Sets up the game (check the game rules)
         */
        void setup();

        /**
         * @brief Plays the turn
         * @return true if the game ends, false otherwise
         */
        bool play();

        /**
         * @brief Gets the winner of the game
         * @return The name of the winner followed by its score, e.g. "Player 1 (500)"
         * @note If the game is not over, return an empty string ("")
         */
        std::string get_winner() const;

        /**
         * @brief Prints the current state of the game
         * @param os The output stream
         * @param game The game instance
         * @return The output stream
         * @note A sample output is:
         *      ```
         *      Draw: [9B, 9R, DR, 6R, 5B, SB, 3R, 6R, 7B, SR, 2R, 9B, 1B, 8R, 8B, 5B, 4R, 3B, 0R, 1R, 5R]
         *      Discard: [2B]
         *      Current: Player 2
         *      Direction: Right
         *      Player 1: [7R, 6B, 7B, 3R, 1R, 2B, RR]
         *      Player 2: [SR, 4R, 6B, RR, 8B, RB, 0B]
         *      Player 3: [9R, 4B, 5R, 8R, 4B, RB, 1B]
         *      Player 4: [DB, 2R, 3B, DR, 7R, SB, DB]
         *      ```
         *      For the draw and discard piles, the card on top should be shown at the start
         *      The players are represented by their name (not Player+index or so)
         */
        friend std::ostream &operator<<(std::ostream &os, const Game &game);

        friend class NumberCard;

        friend class SkipCard;

        friend class ReverseCard;

        friend class DrawTwoCard;
    };

    /**
     * @brief A number card, holds a number and a color
     * @note Its string representation is the number followed by the color, e.g. "1B", "2R"
     */
    class NumberCard : public Card /* TODO */
    {
    private:
        int face_num;

    public:
        NumberCard(int face_nm, std::string colo)
        {
            color = colo;
            face_num = face_nm;
        }
        std::string to_string() const override
        {
            std::string s = (char)(face_num + '0') + color;
            return s;
        }
        const int get_point() const override
        {
            return face_num;
        }
        bool is_available(const Game &game) const override
        {
            if (game.discard.top()->get_color() == color || game.discard.top()->get_point() == face_num)
            {
                return true;
            }
            return false;
        }
        void effect(Game &game) const override
        {
            return;
        }
    };

    /**
     * @brief A skip card, holds a color
     * @note Its string representation is "S" followed by the color, e.g. "SB", "SR"
     */
    class SkipCard : public Card
    {
    public:
        SkipCard(std::string colo)
        {
            color = colo;
        }
        std::string to_string() const override
        {
            std::string s = 'S' + color;
            return s;
        }
        const int get_point() const override
        {
            return 20;
        }
        bool is_available(const Game &game) const override
        {
            if (game.discard.top()->get_color() == color || game.discard.top()->to_string()[0] == 'S')
            {
                return true;
            }
            return false;
        }
        void effect(Game &game) const override
        {
            if (game.current_player_index == game.players.size() - 1 && game.direction == 1)
            {
                game.current_player_index = 0;
            }
            else if (game.current_player_index == 0 && game.direction == -1)
            {
                game.current_player_index = game.players.size() - 1;
            }
            else
            {
                game.current_player_index += game.direction;
            }
        }
    };

    /**
     * @brief A reverse card, holds a color
     * @note Its string representation is "R" followed by the color, e.g. "RB", "RR"
     */
    class ReverseCard : public Card
    {
    public:
        ReverseCard(std::string colo)
        {
            color = colo;
        }
        std::string to_string() const override
        {
            std::string s = 'R' + color;
            return s;
        }
        const int get_point() const override
        {
            return 30;
        }
        bool is_available(const Game &game) const override
        {
            if (game.discard.top()->get_color() == color || game.discard.top()->to_string()[0] == 'R')
            {
                return true;
            }
            return false;
        }
        void effect(Game &game) const override
        {
            game.direction = -game.direction;
        }
    };

    /**
     * @brief A draw two card, holds a color
     * @note Its string representation is "D" followed by the color, e.g. "DB", "DR"
     */
    class DrawTwoCard : public Card
    {
    public:
        DrawTwoCard(std::string colo)
        {
            color = colo;
        }
        std::string to_string() const override
        {
            std::string s = 'D' + color;
            return s;
        }
        const int get_point() const override
        {
            return 40;
        }
        bool is_available(const Game &game) const override
        {
            if (game.discard.top()->get_color() == color || game.discard.top()->to_string()[0] == 'D')
            {
                return true;
            }
            return false;
        }
        void effect(Game &game) const override
        {
            if (game.draw.size() == 1)
            {
                int next_player;
                if (game.current_player_index == game.players.size() - 1 && game.direction == 1)
                {
                    next_player = 0;
                }
                else if (game.current_player_index == 0 && game.direction == -1)
                {
                    next_player = game.players.size() - 1;
                }
                else
                {
                    next_player = game.current_player_index + game.direction;
                }
                game.players[next_player]->getHand().push_back(game.draw.top());
                game.draw.pop();
                const Card *topcard = game.discard.top();
                game.discard.pop();
                shuffle_stack(game.discard);
                while (!game.discard.empty())
                {
                    game.draw.push(game.discard.top());
                    game.discard.pop();
                }
                game.discard.push(topcard);
                game.players[next_player]->getHand().push_back(game.draw.top());
                game.draw.pop();
            }
            else if (game.draw.size() == 0)
            {

                int next_player;
                if (game.current_player_index == game.players.size() - 1 && game.direction == 1)
                {
                    next_player = 0;
                }
                else if (game.current_player_index == 0 && game.direction == -1)
                {
                    next_player = game.players.size() - 1;
                }
                else
                {
                    next_player = game.current_player_index + game.direction;
                }
                const Card *topcard = game.discard.top();
                game.discard.pop();
                shuffle_stack(game.discard);
                while (!game.discard.empty())
                {
                    game.draw.push(game.discard.top());
                    game.discard.pop();
                }
                game.discard.push(topcard);
                game.players[next_player]->getHand().push_back(game.draw.top());
                game.draw.pop();
            }
            else
            {
                int next_player;
                if (game.current_player_index == game.players.size() - 1 && game.direction == 1)
                {
                    next_player = 0;
                }
                else if (game.current_player_index == 0 && game.direction == -1)
                {
                    next_player = game.players.size() - 1;
                }
                else
                {
                    next_player = game.current_player_index + game.direction;
                }
                game.players[next_player]->getHand().push_back(game.draw.top());
                game.draw.pop();
                game.players[next_player]->getHand().push_back(game.draw.top());
                game.draw.pop();
            }
            if (game.current_player_index == game.players.size() - 1 && game.direction == 1)
            {
                game.current_player_index = 0;
            }
            else if (game.current_player_index == 0 && game.direction == -1)
            {
                game.current_player_index = game.players.size() - 1;
            }
            else
            {
                game.current_player_index += game.direction;
            }
        }
    };
    Game::Game(std::initializer_list<Player *> players)
    {
        int player_num = players.size();
        if (player_num > 4 || player_num < 2)
        {
            throw std::invalid_argument("number of players invalid");
        }

        for (auto &sub : players)
        {
            this->players.push_back(sub);
        }
        Card *zero_card_red = new NumberCard(0, "R");
        Card *zero_card_blue = new NumberCard(0, "B");
        draw.push(zero_card_blue);
        draw.push(zero_card_red);
        for (int i = 1; i < 10; i++)
        {
            Card *nbcard = new NumberCard(i, "R");
            Card *nbcard2 = new NumberCard(i, "R");
            Card *nbcard3 = new NumberCard(i, "B");
            Card *nbcard4 = new NumberCard(i, "B");
            draw.push(nbcard);
            draw.push(nbcard2);
            draw.push(nbcard3);
            draw.push(nbcard4);
        }
        for (int i = 0; i < 2; i++)
        {
            Card *skip_red = new SkipCard("R");
            Card *skip_black = new SkipCard("B");
            Card *reverse_red = new ReverseCard("R");
            Card *reverse_black = new ReverseCard("B");
            Card *draw2_r = new DrawTwoCard("R");
            Card *draw2_b = new DrawTwoCard("B");

            draw.push(skip_black);
            draw.push(skip_red);
            draw.push(reverse_red);
            draw.push(reverse_black);
            draw.push(draw2_b);
            draw.push(draw2_r);
        }
    }
    void Game::setup()
    {
        shuffle_stack(draw);
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < players.size(); j++)
            {
                players[j]->getHand().push_back(draw.top());
                draw.pop();
            }
        }

        discard.push(draw.top());
        draw.pop();

        current_player_index = 1;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os << "Draw: " << stack_to_string(game.draw) << std::endl;
        os << "Discard: " << stack_to_string(game.discard) << std::endl;
        os << "Current: " << game.players[game.current_player_index]->getPlayerName() << std::endl;
        if (game.direction == 1)
        {
            os << "Direction: Right" << std::endl;
        }
        else
        {
            os << "Direction: Left" << std::endl;
        }
        for (int i = 0; i < game.players.size(); i++)
        {
            os << game.players[i]->getPlayerName() << ": " << vector_to_string(game.players[i]->getHand()) << std::endl;
        }
        return os;
    }
    std::string Game::get_winner() const
    {
        int has_winner = 0;
        int winner_index = -1;
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->getHand().empty())
            {
                has_winner = 1;
                winner_index = i;
                break;
            }
        }
        if (has_winner)
        {
            int sum = 0;
            for (int i = 0; i < players.size(); i++)
            {
                if (i != winner_index)
                {
                    for (int j = 0; j < players[i]->getHand().size(); j++)
                    {
                        sum += players[i]->getHand()[j]->get_point();
                    }       
                }
            }
            std::string tmp = players[winner_index]->getPlayerName();  
            tmp = tmp + " (" + std::to_string(sum) + ")";
            return tmp;
        }
        else{
            return "";
        }
    }
    bool Game::play()
    {
        Player *cur_player = players[current_player_index];
        int has_playable = 0;
        for (int i = 0; i < cur_player->getHand().size(); i++)
        {
            if (cur_player->getHand()[i]->is_available(*this))
            {
                has_playable = 1;
                const Card *c = cur_player->getHand()[i];
                // std::cout << c->to_string() << std::endl;
                c->effect(*this);
                cur_player->getHand().erase(cur_player->getHand().begin() + i);
                discard.push(c);
                break;
            }
        }
        if (has_playable == 0)
        {
            if (!draw.empty())
            {
                cur_player->getHand().push_back(draw.top());
                draw.pop();
            }
            else{
                const Card * top_discard = discard.top();
                discard.pop();
                shuffle_stack(discard);
                while (!discard.empty())
                {
                    draw.push(discard.top());
                    discard.pop();
                }
                cur_player->getHand().push_back(draw.top());
                draw.pop();
                discard.push(top_discard);
            }
        }
        
        if (current_player_index == players.size() - 1 && direction == 1)
        {
            current_player_index = 0;
        }
        else if (current_player_index == 0 && direction == -1)
        {
            current_player_index = players.size() - 1;
        }
        else
        {
            current_player_index += direction;
        }
        if (cur_player->getHand().empty())
        {
            return true;
        }
        return false;
    }
}
