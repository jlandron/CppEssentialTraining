#include <iostream>
#include <sstream>

using namespace std;
//--------------------------------------Factory Method-----------------------------------------------\
#pragma region Factory
// Product from which the concrete products will inherit from 
class Coffee{
protected:
	string _type;
public:
	Coffee(){
	}
	string getType(){
		return _type;
	}
};
// One concrete class
class Espresso : public Coffee{
public:
	Espresso() : Coffee(){
        _type = "Espresso";
		cout << endl << "Making a cup of espresso" << endl;
		cout << "Grind and brew one scoop of espresso beans." << endl;
	}
};
// Another concrete class
class Cappuccino : public Coffee{
public:
	Cappuccino() : Coffee(){
        _type = "Cappuccino";
		cout << endl << "Making a cup of cappuccino" << endl;
		cout << "Grind and brew one scoop of espresso beans." << endl;
		cout << "Heat and foam milk." << endl;
	}
};
class CoffeMakerFactory{
    private:
        Coffee * _coffee;
    public:
        Coffee * GetCoffee(){
            int choice;

            cout << "select type of coffee to make: " << endl;
            cout << "1: Expresso" << endl;
            cout << "2: Cappuccino" << endl;
            cout << "Selection: ";
            cin >> choice;

            switch(choice){
                case 1:
                    return new Espresso;
                case 2:
                    return new Cappuccino;
                default:
                    cout << "invalid selection " << endl;
                    return NULL;
            }
        }
};
#pragma endregion Factory
//--------------------------------------Abstrct Factory-------------------------------------------
#pragma region AbFactory
//Door Objects
class Door{  //Abstract class
public:
	Door(){
	}
	virtual void Open() = 0;
};
//concrete classes
class GasCarDoor : public Door{
public:
	GasCarDoor(){
		cout << "Making a door for a gas car." << endl;
	}
	void Open(){
		cout << "click" << endl;
	}
};
class ElectricCarDoor : public Door{
public:
	ElectricCarDoor(){
		cout << "Making a door for an electric car" << endl;
	}
	void Open(){
		cout << "shhhhh" << endl;
	}
};
//Engine objects
class Engine{  //Abstract class
protected:
	string _sound;
public:
	Engine(){
		_sound = "";
	}
	virtual void Run() = 0;
};
//concrete classes
class GasEngine : public Engine{
public:
	GasEngine(){
		_sound = "vroom";
		cout << "Making a gas engine." << endl;
	}
	void Run(){
		cout << _sound << endl;
	}
};
class ElectricEngine : public Engine{
public:
	ElectricEngine(){
		_sound = "SHHHH";
		cout << "Making an electric engine." << endl;
	}
	void Run(){
		cout << _sound << endl;
	}
};
//Factories
class CarFactory{
    public:
        virtual Door* BuildDoor() = 0;
        virtual Engine* BuildEngine() = 0;
};
class GasCarFactory : public CarFactory{\
    public:
        Door* BuildDoor(){
            return new GasCarDoor();
        }
        Engine* BuildEngine(){
            return new GasEngine();
        }
};
class ElectricCarFactory : public CarFactory{\
    public:
        Door* BuildDoor(){
            return new ElectricCarDoor();
        }
        Engine* BuildEngine(){
            return new ElectricEngine();
        }
};

#pragma endregion AbFactory
//---------------------------------------------Builder------------------------------------------
#pragma region Builder
// Base Entree class
class Entree{
protected:
	string _entree;
public:
	const string *getEntree(){
		return &_entree;
	}
};
// Derived Buger class
class Burger : public Entree{
public:
	Burger(){
		cout << "\n Grill burger patty, add tomatoes and place them in a bun";
		_entree = "hamburger";
	}
};
// Derived Hotdog class
class Hotdog : public Entree{
public:
	Hotdog(){
		cout << "\n Cook sausage and place it in a bun";
		_entree = "hotdog";
	}
};
// Base Side class
class Side{
protected:
	string _side;
public:
	string getSide(){
		return _side;
	}
};
//Derived Fries class
class Fries : public Side{
public:
	Fries(){
		cout << "\n Fry and season potatoes";
		_side = "fries";
	}
};
//Derived Salad class
class Salad : public Side{
public:
	Salad(){
		cout << "\n Toss greens and dressing together";
		_side = "salad";
	}
};
class Drink{
protected:
	string _drink;
public:
	Drink(){
		cout << "\n Fill cup with soda" << endl;
		_drink = "soda";
	}
	string getDrink(){
		return _drink;
	}
};
// Complex MealCombo object that contains an Entree, a Side and a Drink object
class MealCombo{
private:
	Entree *entree;
	Side *side;
	Drink *drink;
	stringstream _bag;
public:
	MealCombo(const string type){
		_bag << type << " meal combo: " << type;
	}
	void setEntree(Entree *e){
		entree = e;
	}
	void setSide(Side *s){
		side = s;
	}
	void setDrink(Drink *d){
		drink = d;
	}
	const string openMealBag(){
		_bag << " " << side->getSide() << " " << drink->getDrink();
		string _bagString;
        _bagString = _bag.str();
        return _bagString;
	}
};
// Base Builder
class MealBuilder{
    protected:
        MealCombo * _meal;
    public:
        virtual void cookEntree(){};
        virtual void cookSide(){};
        virtual void fillDrink(){};
        MealCombo* getMeal(){
            return _meal;
        }
};
//Concrete Builder for a Burger Meal which has a burger, fries and a drink
class BurgerMeal : public MealBuilder{
    public:
    BurgerMeal(){
        _meal = new MealCombo("Burger");
    }
    void cookEntree(){
        Burger *burger = new Burger;
        _meal->setEntree(burger);
    }
    void cookSide(){
        Fries *fries = new Fries;
        _meal->setSide(fries);
    }
    void fillDrink(){
        Drink *drink = new Drink;
        _meal->setDrink(drink);
    }
};
//Concrete Builder for a Hotdog Meal which has a hotdog, salad and a drink
class HotdogMeal : public MealBuilder{
public:
	HotdogMeal(){
		_meal = new MealCombo("Hotdog");
	}
	void cookEntree(){
		Hotdog *hotdog = new Hotdog;
		_meal->setEntree(hotdog);
	}
	void cookSide(){
		Salad *caesar = new Salad;
		_meal->setSide(caesar);
	}
	void fillDrink(){
		Drink *drink = new Drink;
		_meal->setDrink(drink);
	}
};
#pragma endregion Builder
//---------------------------------------------Singleton------------------------------------------
#pragma region Singleton

class Leader{
    private:
    static Leader* _instance;
        Leader(){
            std::cout << "New Leader Elected" << std::endl;
        }
    public:
        static Leader * getInstance(){
            if(_instance == NULL){
                _instance = new Leader;
            }
        return _instance;
        }
        void giveSpeech(){
            std::cout << "Adress the public" << std::endl;
        }
};
Leader* Leader::_instance = NULL;

#pragma endregion Singleton
//----------------------------------------------main----------------------------------------------
int main() {
#pragma region FactoryMain
//Factory Method
    // CoffeMakerFactory coffeeMachine;
    // Coffee *cup;
    // cup = coffeeMachine.GetCoffee();
    // cout << endl << "You had asked for a(n) " << cup->getType() << endl;
#pragma endregion FactoryMain
//Abstrct Factory
#pragma region AbFactoryMain
    // CarFactory* CarPlant;
    // int choice;
    // cout << "Select a car type: " << endl;
	// cout << "1: Gasoline" << endl;
	// cout << "2: Electric" << endl;
	// cout << "Selection: ";
	// cin >> choice;
	// cout << endl;
    // switch(choice){
    //     case 1:
    //         CarPlant = new GasCarFactory;
    //         break;
    //     case 2:
    //         CarPlant = new ElectricCarFactory;
    //         break;
    //     default:
    //         cout << "Invalid selection" << endl;
    //         CarPlant = NULL;
    //         break;
    // }
    // if(CarPlant != NULL){
    //     Door* myDoor = CarPlant->BuildDoor();
    //     Engine* myEngine = CarPlant->BuildEngine();

    //     myDoor->Open();
    //     myEngine->Run();
    // }
#pragma endregion AbFactoryMain
//Builder
#pragma region BuilderMain
    // MealBuilder* cook = new MealBuilder;
	// MealCombo* meal;
    // int choice;
    // // Prompt user for their meal choice
	// cout << "Select a meal: " << endl;
	// cout << "1: Hamburger Meal" << endl;
	// cout << "2: Hotdog Meal" << endl;
	// cout << "Selection: ";
	// cin >> choice;
	// cout << endl;    

	// // Instantiate the apporpriate builder based on user input
	// switch(choice){
    //     case 1:
    //         cook = new BurgerMeal;
    //         break;
    //     case 2:
    //         cook = new HotdogMeal;
    //         break;
    //     default:
    //         cout << "Invalid Selection" << endl;
    //         cook = NULL;
    //         break;
    // }
	// cout << "Making selected meal" << endl; 
	// // Build the complex object
    // cook->cookEntree();
    // cook->cookSide();
    // cook->fillDrink();
    // meal = cook->getMeal();
    // cout << meal->openMealBag() << endl;
#pragma endregion BuilderMain
//Singleton
    Leader::getInstance()->giveSpeech();
    Leader *elected = elected->getInstance();
    elected->giveSpeech();
}