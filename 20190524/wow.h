#ifndef _WOW_H_
#define _WOW_H_
#include <string>
using std::string;
enum flag 
{
    NONE,
    RED,
    BLUE
};
class Creature;
class City;
class Creature
{
public:
    Creature(int id, int hp, int atk)
    :_id(id),_hp(hp),_attack(atk)
    {}
    virtual ~Creature(){};
    void graspHp()
    {

    }
    virtual void activeAttack(Creature &opponet) = 0;
    virtual void passiveAttack(Creature &opponet) = 0;
    virtual void killoff(Creature &opponet) = 0;
    virtual void die(Creature &oppoent) = 0;
    void move()
    {

    }
protected:
    int _id;
    int _hp;
    int _attack;
private:
    City& _city;
};
class Iceman: private Creature
{
public:
    void wrath()
    {

    }
private:
    bool _isWrath;
};

class City
{
protected:

};
class Director: private City
{
public:
    Director( int side, int hpPotention)
    :_side(side),_hpPotention(hpPotention)
    {}
    virtual ~Director()
    {}
    Creature &create();
protected:
    int _side;
    int _hpPotention;
};
class CityList
{
    void initCity()
    {
        if(_pCity == nullptr)
        {
            Director blue = new Director();
            _pCity = new CityList();
        }
    }
    Director& getRed()
    {}
    Director& getBlue()
    {}
private:
    CityList(int cnt,Director& red,Director& blue)
    :_count(cnt),_red(red),_blue(blue)
    {
        for(int i = 1; i <= _count; i++)
        {

        }
    }
    static CityList* _pCity;
    int _count;
    Director& _red;
    Director& _blue;
}
CityList* CityList::_pCity = nullptr; 
#endif
