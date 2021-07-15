// OOP_5_task.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1 задание
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Pair1
{
private:
    T first1;
    T second1;

public:
    Pair1()
    {
        first1=0;
        second1=0;
    }

    Pair1( T t1,  T t2) : first1(t1), second1(t2)
    {
       
    }

    ~Pair1()
    {
        
    }

    T first() const
    {
        return first1;
    }
    T second() const
    {
        return second1;
    }

};

//int main()
//{
//    Pair1<int> p1(6, 9);
//    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
//    const Pair1<double> p2(3.4, 7.8);
//    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
//    return 0;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2 задание
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T1, class T2> 
class Pair
{
private:
    T1 first1;
    T2 second1;

public:
    Pair()
    {
        first1 = 0;
        second1 = 0;
    }

    Pair(T1 t1, T2 t2) : first1(t1), second1(t2)
    {

    }

    ~Pair()
    {

    }

    T1 first() const
    {
        return first1;
    }
    T2 second() const
    {
        return second1;
    }

};


//int main()
//{
//    Pair<int, double> p1(6, 7.8);
//    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
//
//    const Pair<double, int> p2(3.4, 5);
//    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
//
//    return 0;
//}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3 задание
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class T2>
class StringValuePair  : public Pair<string, T2> 
{   
public:
    StringValuePair(string str, T2 t2) : Pair<string, T2>(str, t2) {};
};
    


    int main()
{
        StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
    return 0;
}

///////////////////////////
class Card
 {
 public:
    enum suit
    {
        CLUBS,
        SPADES,
        HEARTS,
        DIMONDS
        };
    enum rank
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 10,
        QUEEN = 10,
        KING = 10,

    };

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    void Flip();
    int GetValue() const;
        
 private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s),  m_IsFaceUp(ifu) {}
    
int Card::GetValue()const
    {
        int value = 0;
        if(m_IsFaceUp)
        {
            value = m_Rank;
            if (value>10)
            {
                value = 10;
            }
        }
        return value;
    }        
    
void Card::Flip()   
    {
        m_IsFaceUp = !(m_IsFaceUp);
    }


////////////////////////////


class Hand
{
public:
    Hand();
    // виртуальный деструктор
    virtual ~Hand();

    // добавляет карту в руку
    void Add(Card* pCard);

    // очищает руку от карт
    void Clear();

    //получает сумму очков карт в руке, присваивая тузу
    // значение 1 или 11 в зависимости от ситуации
    int GetTotal() const;

protected:
    vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}
// деструктор по-прежнему виртуальный
// это уже можно не обозначать
Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}


void Hand::Clear()
{
    // проходит по вектору, освобождая всю память в куче
    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete* iter;
        *iter = 0;
    }
    // очищает вектор указателей
    m_Cards.clear();
}


int Hand::GetTotal() const
{
    // если карт в руке нет, возвращает значение 0
    if (m_Cards.empty())
    {
        return 0;
    }

    //если первая карта имеет значение 0, то она лежит рубашкой вверх:
    // вернуть значение 0
    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }

    // находит сумму очков всех карт, каждый туз дает 1 очко
    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }

    // определяет, держит ли рука туз
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }

    // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
    if (containsAce && total <= 11)
    {
        // добавляем только 10 очков, поскольку мы уже добавили
        // за каждый туз по одному очку
        total += 10;
    }

    return total;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4 задание
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class GenericPlayer: public Hand

{
private:
    string name;
public:
    bool virtual IsHitting() const =0;
        
 
    
    bool   IsBoosted()
    {   if((GetTotal())<21)
        { 
            return true; 
        }       
        else 
        {
            return false;
        }

    }
     
    void Bust()
    {
        std::cout << "Player: " << name << " has overdraw" << endl;
    }
       

};