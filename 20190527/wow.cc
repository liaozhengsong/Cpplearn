#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <fstream>
#define CTYPE 5
using namespace std;
enum TYPE
{
    DRAGON,
    NINJA,
    ICEMAN,
    LION,
    WOLF
};
enum CAMP
{
    NONE,
    RED,
    BLUE
};
//ofstream cout("out.txt");
//FILE* fp = fopen("out.txt","w");
FILE *fp = stdout;
class Creature;
class Headquarter
{
public:
    Headquarter(int camp,int healthPotential)
        : _isCreate(nullptr)
          , _conquerCnt(0)
          , _healthPotential(healthPotential)
          , _camp(camp)
          , _creatureCount(0)
    {}
    ~Headquarter();
    Creature *create(int);
    bool isCreate(int);
    void CheckHealth(int,Creature&,int);
    void GetHealth(int*,int);
    void Report();
    static vector<int> hpList;
    static vector<int> atkList;
    static vector<int> redCreateList;
    static vector<int> blueCreateList;
    Creature* _isCreate;
    int _conquerCnt;
    int _healthPotential;
private:
    int _camp;
    int _creatureCount;
};
void printT(int);
struct node 
{
    int creatureCnt;
    Creature *red;
    Creature *tored;
    Creature *blue;
    Creature *toblue;
    int flag;
    int current;
    int health;
};

class Creature 
{
public:
    string CheckCamp()
    {
        if(_camp == RED)
            return "red";
        else if(_camp == BLUE)
            return "blue";
        return "none";
    }
    virtual string CheckType()
    {
        return "creature";
    }
    int GetNo()
    {
        return _NO;
    }
    Creature(int camp,int type,int NO, int initHealth, int attack)
        : _isWin(false)
          , _camp(camp)
          , _type(type)
          , _NO(NO) 
          , _initHealth(initHealth)
          , _attack(attack)
    {
    #if 0
        cout << CheckCamp() << " "
            << _nameArr[_type] << " "
            << GetNo() << " born"
            << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d born\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo());
    #endif
    }

    void March(int destcity)
    {
        Wrath();
    #if 0
        cout << CheckCamp()  << " "
            << CheckType() << " "
            << GetNo()<< " marched to city " 
            << destcity << " with " 
            << _initHealth << " elements and force "
            << _attack << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d marched to city %d with %d elements and force %d\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo(),destcity,_initHealth,_attack);    
    #endif
        _isWin = false;
    }

    void ToHead()
    {
        Wrath();
    #if 0
        cout << CheckCamp()  << " "
            << CheckType() << " "
            << GetNo() << " reached "; 
    #endif
    #if 1
        fprintf(fp,"%s %s %d reached",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo());   
    #endif
    #if 0
        if(_camp == RED)
            cout << "blue ";
        else if(_camp == BLUE)
            cout << "red ";
           
        cout << "headquarter with " 
            << _initHealth << " elements and force "
            << _attack << endl;
    #endif
    #if 1
        if(_camp == RED)
            fprintf(fp," blue headquarter with %d elements and force %d\n",_initHealth,_attack);
        else
            fprintf(fp," red headquarter with %d elements and force %d\n",_initHealth,_attack);
    #endif
    }

    virtual ~Creature() {}

    void GetAward(Headquarter &h,int nelement)
    {
        if(h._healthPotential < 8 || nelement == 0)
        {

        }
        else
        {
            Heal(8);
            h._healthPotential -= 8;
        }
    }
    void Heal(int pnt)
    {
        this->_initHealth += pnt;
    }
    bool GetAttack(int atk, int icity, int minute)
    {//击杀返回false
        this->_initHealth -= atk;
        if(_initHealth <= 0)
        {
            this->Die(icity,minute);
            return false;
        }
        else 
            return true;
    }
    int GetInitHealth()
    {
        return _initHealth;
    }
    virtual bool Fightback(Creature &opponent, int icity, int minute)
    {//击杀返回false
        _isWin = false;
        printT(minute);
    #if 0
        cout << CheckCamp() << " "
            << CheckType() << " "
            << GetNo() << " fought back against "
            << opponent.CheckCamp() << " "
            << opponent.CheckType() << " "
            << opponent.GetNo() << " in city "
            << icity << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d fought back against %s %s %d in city %d\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo(),
                                                                    opponent.CheckCamp().c_str(),opponent.CheckType().c_str(),opponent.GetNo(),
                                                                    icity);
    #endif
        int tmp = opponent._initHealth;
        if(opponent.GetAttack(this->_attack/2,icity,minute))
        {
            _isWin = false;
            return true;
        }
        else
        {
            opponent._isWin = false;
            opponent.Feed(*this,tmp);
            _isWin = true;
            return false;
        }
    }
    virtual void Yell(int icity, int minute)
    {
        return;
    }
    virtual void Wrath()
    {
        return;
    }
    void Attack(Creature &opponent, int icity, int minute)
    {
        _isWin = false;
        printT(minute);
    #if 0
        cout << CheckCamp()  << " "
            << CheckType() << " "
            << GetNo() << " attacked "
            << opponent.CheckCamp() << " "
            << opponent.CheckType() <<  " "
            << opponent.GetNo() << " in city "
            << icity << " with "
            << _initHealth << " elements and force "
            << _attack << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo(),
                                                                    opponent.CheckCamp().c_str(),opponent.CheckType().c_str(),opponent.GetNo(),
                                                                    icity,_initHealth,_attack);
    #endif
        int tmp = opponent._initHealth;
        if(opponent.GetAttack(this->_attack,icity,minute))
        {
            if(opponent.Fightback(*this,icity,minute))
                Yell(icity,minute);
            _isWin = false;
        }
        else
        {
            BloodSuck();
            opponent.Feed(*this,tmp);
            opponent._isWin = false;
            Yell(icity,minute);
            _isWin = true;
        }
    }
    virtual void Feed(Creature &opponent,int heal)
    {
        return;
    }
    virtual void BloodSuck()
    {
        return;
    }
    void Die(int icity, int minute)
    {
        printT(minute);
    #if 0
        cout << CheckCamp()  << " "
            << CheckType() << " "
            << GetNo() << " was killed in city "
            << icity << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d was killed in city %d\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo(),icity);    
    #endif
    }
    bool _isWin;
protected:
    int _camp;
    int _type;
    int _NO;
    int _initHealth;
    int _attack;
    static vector<string> _nameArr;
};
vector<string> Creature::_nameArr = {"dragon","ninja","iceman","lion","wolf"};
class Dragon: public Creature
{
public:
    Dragon(int camp, int type, int NO, int initHealth, int attack)
        : Creature(camp,type,NO,initHealth,attack)
    {
    }
    string CheckType()
    {
        return "dragon";
    }
    virtual ~Dragon()
    {}
    virtual void Yell(int icity,int minute)
    {
        printT(minute);
    #if 0
        cout << CheckCamp() << " "
            << CheckType() << " "
            << GetNo() << " yelled in city "
            << icity << endl;
    #endif
    #if 1
        fprintf(fp,"%s %s %d yelled in city %d\n",CheckCamp().c_str(),_nameArr[_type].c_str(),GetNo(),icity);    
    #endif
    }
};
class Ninja: public Creature
{
public:
    Ninja(int camp, int type, int NO, int initHealth, int attack)
        : Creature(camp,type,NO,initHealth,attack)
    {
    }
    string CheckType()
    {
        return "ninja";
    }
    virtual ~Ninja()
    {}
    virtual bool Fightback(Creature &opponent, int icity, int minute)
    {
        return true;
    }

};
class Lion: public Creature
{
public:
    Lion(int camp, int type, int NO, int initHealth, int attack)
        : Creature(camp,type,NO,initHealth,attack)
    {
    }
    string CheckType()
    {
        return "lion";
    }
    virtual ~Lion()
    {}
    virtual void Feed(Creature &opponent, int heal)
    {
        opponent.Heal(heal);
    }
};
class Wolf: public Creature
{
public:
    Wolf(int camp, int type, int NO, int initHealth , int attack)
        : Creature(camp,type,NO,initHealth,attack)
          , _killedCnt(0)
    {
    }
    string CheckType()
    {
        return "wolf";
    }
    virtual ~Wolf()
    {}
    virtual void BloodSuck()
    {
        ++_killedCnt;
        if(_killedCnt % 2 ==0)
        {
            _attack *= 2;
            _initHealth *= 2;
        }
    }
private:
    int _killedCnt;
};
class Iceman: public Creature
{
public:
    Iceman(int camp, int type, int NO, int initHealth, int attack)
        : Creature(camp,type,NO,initHealth,attack)
          , _wrathCnt(0)
    {
    }
    string CheckType()
    {
        return "iceman";
    }
    virtual ~Iceman()
    {}
    virtual void Wrath()
    {
        ++_wrathCnt;
        if(_wrathCnt == 2)
        {
            _wrathCnt = 0;
            if(_initHealth > 9)
            {
                _initHealth -= 9;
            }
            else
                _initHealth = 1;

            _attack += 20;
        }
    }
private:
    int _wrathCnt;
};
Headquarter::~Headquarter()
{
    if(_isCreate)
        delete _isCreate;
}

void Headquarter::CheckHealth(int health, Creature &cre, int minute)
{
    if(health == 0)
        return;
    printT(minute);
    #if 0
    cout << cre.CheckCamp() << " "
        << cre.CheckType() << " "
        << cre.GetNo() << " earned "
        << health << " elements for his headquarter" << endl;
    #endif
    fprintf(fp,"%s %s %d earned %d elements for his headquarter\n",cre.CheckCamp().c_str(),cre.CheckType().c_str(),cre.GetNo(),health);
}
void Headquarter::GetHealth(int* health,int minute)
{
    _healthPotential += *health;
    *health = 0;
}
bool Headquarter::isCreate(int itoCreate)
{
    int toCreate = hpList[itoCreate];
    if(_healthPotential>= toCreate)
        return true;
    else
        return false;
}

void Headquarter::Report()
{
#if 0
    cout << _healthPotential << " elements in ";
    if(_camp == RED)
        cout << "red ";
    else if(_camp == BLUE)
        cout << "blue ";
    cout << "headquarter" << endl;
#endif 
#if 1
    if(_camp == RED)
        fprintf(fp,"%d elements in red headquarter\n",_healthPotential);
    else
        fprintf(fp,"%d elements in blue headquarter\n",_healthPotential);
#endif
}
Creature *Headquarter::create(int minute)
{
    Creature* pcr = nullptr;
    if(_camp == RED)
    {
        int type = redCreateList[_creatureCount%CTYPE];
        if(isCreate(type))
        {
            printT(minute);
            switch(type)
            {
            case DRAGON:
                pcr = (Creature *) new Dragon(RED,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case NINJA:
                pcr = (Creature *) new Ninja(RED,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case ICEMAN:
                pcr = (Creature *) new Iceman(RED,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case LION:
                pcr = (Creature *) new Lion(RED,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case WOLF:
                pcr = (Creature *) new Wolf(RED,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            }
            ++_creatureCount;
        }
    }
    else if(_camp == BLUE)
    {
        int type = blueCreateList[_creatureCount%CTYPE];
        if(isCreate(type))
        {
            printT(minute);
            switch(type)
            {
            case DRAGON:
                pcr = (Creature *) new Dragon(BLUE,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case NINJA:
                pcr = (Creature *) new Ninja(BLUE,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case ICEMAN:
                pcr = (Creature *) new Iceman(BLUE,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case LION:
                pcr = (Creature *) new Lion(BLUE,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            case WOLF:
                pcr = (Creature *) new Wolf(BLUE,type,_creatureCount+1,hpList[type],atkList[type]);
                _healthPotential -= hpList[type];
                break;
            }
            ++_creatureCount;
        }
    }

    if(pcr == nullptr)
        _isCreate = nullptr;
    else
        _isCreate = pcr;

    return pcr;
}

vector<int> Headquarter::redCreateList = {ICEMAN,LION,WOLF,NINJA,DRAGON};
vector<int> Headquarter::blueCreateList = {LION,DRAGON,NINJA,ICEMAN,WOLF};
vector<int> Headquarter::hpList = {};
vector<int> Headquarter::atkList = {};

void printT(int minute)
{
    int hour = minute/60;
    int remain = minute%60;
#if 0
    cout.width(3);
    cout.fill('0');
    cout << hour << ":";
    cout.width(2);
    cout.fill('0');
    cout << remain << " ";
#endif
    fprintf(fp,"%03d:%02d ",hour,remain);
}
void test0(int totalMinute,int hp, int ncity)
{
    vector<node> city;
    city.clear();

    for(int i = 0; i <= ncity + 1; ++i)
    {
        node cnode = {0, nullptr, nullptr, nullptr, nullptr, 0, NONE, NONE};
        city.push_back(cnode);
    }

    Headquarter::hpList.clear();
    Headquarter::atkList.clear();

    for(int i = DRAGON; i <= WOLF; ++i)
    {
        int tmp;
        cin >> tmp;
        Headquarter::hpList.push_back(tmp);
    }

    for(int i = DRAGON; i <= WOLF; ++i)
    {
        int tmp;
        cin >> tmp;
        Headquarter::atkList.push_back(tmp);
    }

    Headquarter red(RED,hp);
    Headquarter blue(BLUE,hp);
    Creature* ptmp;
    Creature* ptmpred = nullptr;
    Creature* ptmpblue = nullptr;
    int index;
    for(int minute = 0; minute <= totalMinute ; )
    {
        ptmp = red.create(minute);
        if(ptmp)
        {
            city[0].red = ptmp;
        }
        ptmp = blue.create(minute);
        if(ptmp)
        {
            city[city.size()-1].blue = ptmp;
        }
        ptmp = nullptr;
        minute += 10;
        if(minute > totalMinute) return;
        ptmpred = nullptr;
        ptmpblue = nullptr;
        for(auto it = city.begin(); it != city.end(); ++it)
        {
            it->tored = ptmpred;
            ptmpred = it->red;
        }
        for(auto it = city.end()-1; it >= city.begin(); --it)
        {
            it->toblue = ptmpblue;
            ptmpblue = it->blue;
        }
        for(auto &c:city)
        {
            c.red = c.tored;
            c.tored = nullptr;
            c.blue  = c.toblue;
            c.toblue = nullptr;
        }
        //使用3个循环来处理左移和右移
        if(city.begin()->blue)
        {
            printT(minute);
            city.begin()->blue->ToHead();
            delete city.begin()->blue;
            city.begin()->blue = nullptr;
            ++blue._conquerCnt;
            if(blue._conquerCnt >= 2)
            {
                printT(minute);
                // cout << "red headquarter was taken" << endl;
                fprintf(fp,"red headquarter was taken\n");
            }
        }
        for(auto it = city.begin()+1; it != city.end()-1; ++it)
        {
            index = it - city.begin();
            if(it->red)
            {
                printT(minute);
                it->red->March(index);
            }
            if(it->blue)
            {
                printT(minute);
                it->blue->March(index);
            }
        }
        if((city.end()-1)->red)
        {
            printT(minute);
            (city.end()-1)->red->ToHead();
            delete (city.end()-1)->red;
            (city.end()-1)->red = nullptr;
            ++red._conquerCnt;
            if(red._conquerCnt >= 2)
            {
                printT(minute);
                // cout << "blue headquarter was taken" << endl;
                fprintf(fp,"blue headquarter was taken\n");
            }
        }
        if(red._conquerCnt >= 2 || blue._conquerCnt >= 2)
            return;
        minute += 10;
        if(minute > totalMinute) return;

        for(auto &c:city)
        {
            c.health += 10;
        }
        minute += 10;
        if(minute > totalMinute) return;

        for(auto &c:city)
        {
            if(c.red&&!(c.blue))
            {
                red.CheckHealth(c.health,*c.red,minute);
                red.GetHealth(&c.health,minute);
            }
            else if(c.blue&&!(c.red))
            {
                blue.CheckHealth(c.health,*(c.blue),minute);
                blue.GetHealth(&c.health,minute);
            }
        }
        minute += 10;
        if(minute > totalMinute) return;

        for(auto it = city.begin()+1; it != city.end()-1; ++it)
        {
            int icity = it - city.begin();
            if(it->red && it->blue)//发生战斗的地方
            {
                if(it->flag == RED || (it->flag == NONE && (icity % 2 == 1)))
                {
                    it->red->Attack(*(it->blue),icity,minute);
                }
                else if (it->flag == BLUE || (it->flag == NONE && (icity %2 == 0)))
                {
                    it->blue->Attack(*(it->red),icity,minute);
                }
            }
            else 
                continue;

            if(it->blue && it->blue->_isWin)
            {
                //delete it->red;
                it->red = nullptr;
                blue.CheckHealth(it->health,*it->blue,minute);//检查是否发放奖励
                if(it->current == BLUE && it->flag != BLUE)//检查旗子
                {
                    it->flag = BLUE;
                    printT(minute);
#if 0
                    cout << "blue flag raised in city "
                        << icity << endl;
#endif
#if 1
                    fprintf(fp,"blue flag raised in city %d\n",icity);    
#endif
                }
                else
                {
                    it->current = BLUE;
                }
            }
            else if(it->red && it->red->_isWin)
            {
                //delete it->blue;
                it->blue = nullptr;//清理失败者
                red.CheckHealth(it->health,*it->red,minute);
                if(it->current == RED && it->flag != RED)
                {
                    it->flag = RED;
                    printT(minute);
#if 0
                    cout << "red flag raised in city "
                        << icity << endl;
#endif                    
#if 1
                    fprintf(fp,"red flag raised in city %d\n",icity);    
#endif
                }
                else
                {
                    it->current = RED;
                }
            }//打印奖励信息
            else if(it->blue && it->red)
            {
                it->current = NONE;
            }//清理旗子
        }//发生战斗

        for(auto it = city.begin()+1; it != city.end()-1; ++it)
        {
            if(it->blue && it->blue->_isWin)
            {
                it->blue->GetAward(blue,it->health);
            }
        }//从头开始统计b的战果

        for(auto it = city.end()-2; it != city.begin(); --it)
        {
            if(it->red &&it->red->_isWin)
            {
                it->red->GetAward(red,it->health);//给战士奖励
            }
        }//从末尾开始统计a的战果

        for(auto &c:city)
        {
            if(c.red && c.red->_isWin)
            {
                red.GetHealth(&c.health,minute);
            }
            if(c.blue && c.blue->_isWin)
            {
                blue.GetHealth(&c.health,minute);
            }
        }//收取生命元
        minute += 10;
        if(minute > totalMinute) return;

        printT(minute);
        red.Report();
        printT(minute);
        blue.Report();
        minute += 10;
        if(minute > totalMinute) return;
    }
}

int main()
{
    int ncase;
    cin >> ncase;
    for(int i = 1; i <= ncase; ++i)
    {
       // cout << "Case:" << i << endl;
        fprintf(fp,"Case:%d\n",i);
        int totalMinute;
        int hp;
        int ncity;
        cin >> hp >> ncity >> totalMinute;
        test0(totalMinute, hp, ncity);
    }
    return 0;
}
