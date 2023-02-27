# Façade Pattern  

복잡한 서브 시스템 앞에 단순한 인터페이스를 두기 위한 패턴이다.  
말보다 예시가 더 간단할 정도로 단순한 패턴이다.  
&nbsp;  

우리가 요리를 배달시키는 경우 많은 과정을 거친다.  
식당에서 요리를 만들어야 하고 배달해야 하며 배달원과 식당을 연결해주는 배달의 민족, 요기요와 같은 배달 서비스 업체가 있어야 한다.  
어러한 배경의 음식 배달 시스템을 구축해보자.  
&nbsp;  

일단 밑과 같은 요리 클래스가 있다.  
```c++
struct Cuisine
{
    std::string food_name;
    std::vector<std::string> ingredients;
};
```
요리는 이름과 각종 재료들로 이루어져 있다.  
&nbsp;  

식당 클래스는 밑과 같다.  
```c++
struct Restaurant
{
    std::string name;
    std::unordered_map<std::string, std::vector<std::string>> menu;
    std::pair<float, float> location;

    Restaurant(const std::string name, const std::unordered_map<std::string, std::vector<std::string>> menu, const std::pair<float, float> location) : name{name}, menu{menu}, location{location}
    {
    }

    Cuisine &&make_cuisine(const std::string &food_name)
    {
        Cuisine cuisine;
        if (menu.find(food_name) == menu.end())
            return std::move(cuisine);

        cuisine.food_name = food_name;
        cuisine.ingredients = menu[food_name];
        return std::move(cuisine);
    }
};
```
식당은 이름, 메뉴, 위치가 멤버 변수로 존재하며 메뉴에 있는 음식을 제공할 수 있어야 한다.  
세부 구현보다 전체적인 구조를 봐라.  
&nbsp;  

배달원 클래스는 밑과 같다.  
```c++
struct DeliveryMan
{
    std::string name;
    std::pair<float, float> location;

    DeliveryMan(const std::string name, const std::pair<float, float> &location) : name{name}, location{location}
    {
    }

    Cuisine &&delivery(Cuisine &&cuisine, const std::pair<float, float> &restaurant_location, const std::pair<float, float> &destination)
    {
        auto get_distance = [](const std::pair<float, float> &a, const std::pair<float, float> &b) -> float
        {
            return std::sqrtf(std::powf(a.first - b.first, 2) + std::powf(a.second - b.second, 2));
        };

        float distance = get_distance(location, restaurant_location) + get_distance(restaurant_location, destination);

        for (float i = 0; i < distance; i += 0.5)
            std::cout << "Delivering... " << distance - i << "m left!\n";

        return std::move(cuisine);
    }
};
```
배달원은 이름과 현재 위치가 멤버 변수로 존재한다.  
식당에서 음식을 받고 도착지에 배달할 수 있어야 한다.  
&nbsp;  

요기요와 배달의 민족과 같은 배달 서비스 업체에 대한 클래스는 밑과 같다.  
```c++
struct OrderingService
{
    std::string name;
    std::vector<Restaurant> &restaurants;
    std::vector<DeliveryMan> &delivery_men;

    OrderingService(const std::string &name, std::vector<Restaurant> &restaurants, std::vector<DeliveryMan> &delivery_men)
        : name{name}, restaurants{restaurants}, delivery_men{delivery_men}
    {
    }

    DeliveryMan &matching(const Restaurant &restaurant)
    {
        auto get_distance = [](const std::pair<float, float> &a, const std::pair<float, float> &b) -> float
        {
            return std::sqrtf(std::powf(a.first - b.first, 2) + std::powf(a.second - b.second, 2));
        };

        float min_dist = std::numeric_limits<float>::max();
        int closest_delivery_man = 0;
        for (size_t i = 0; i < delivery_men.size(); i++)
        {
            float dist = get_distance(restaurant.location, delivery_men[i].location);
            if (min_dist > dist)
            {
                min_dist = dist;
                closest_delivery_man = i;
            }
        }
        return delivery_men[closest_delivery_man];
    }
};
```
배달 서비스 업체는 빠른 배달을 위해 음식점과 가장 가까운 배달원을 매칭시킬 수 있어야 한다.  
&nbsp;  

식당, 배달원, 배달 서비스 업체에 대한 정보를 모두 알게 되었으니 이를 토대로 배달 시스템을 구축해보자.  
일단 초기화를 진행하자.  
```c++
std::vector<Restaurant> restaurants;
std::vector<DeliveryMan> delivery_men;
std::vector<OrderingService> services;

// 식당 초기화
restaurants.push_back(Restaurant{
    "pizza town",
    {{"potato pizza", {"dough", "potato", "oil", "water", "salt"}}},
    {51.38f, 104.1f}});
restaurants.push_back(Restaurant{
    "pasta mall",
    {{"tomato pasta", {"noodle", "tomato", "oil", "water", "sugar", "parsley"}}},
    {-20.5f, -77.22f}});

// 배달원 초기화
delivery_men.push_back(DeliveryMan{
    "Iron Man",
    {103.f, 58.76f}});
delivery_men.push_back(DeliveryMan{
    "Captin America",
    {-42.f, 13.6f}});
delivery_men.push_back(DeliveryMan{
    "Thor",
    {55.4f, 11.2f}});

// 배달 서비스 초기화
services.push_back(OrderingService{"BeaMin", restaurants, delivery_men});
services.push_back(OrderingService{"Yogiyo", restaurants, delivery_men});
```
식당 2개, 배달원 3명, 배달 서비스 업체 2곳이 있다.  
&nbsp;  

손님이 주문을 하는 프로세스를 작성해보자.  
(30, 1) 위치가 집이고 pizza town에서 potato pizza를 BeaMin 서비스 업체를 통해 주문하려 한다.  
```c++
std::string service_name = "BeaMin";
std::string restaurant_name = "pizza town";
std::string food_name = "potato pizza";
std::pair<float, float> home = {30.f, 1.f};

int restaurant = 0, service = 0;
for (size_t i = 0; i < restaurants.size(); i++)
    if (restaurant_name == restaurants[i].name)
    {
        restaurant = i;
        break;
    }
for (size_t i = 0; i < services.size(); i++)
    if (service_name == services[i].name)
    {
        service = i;
        break;
    }
DeliveryMan &delivery_man = services[service].matching(restaurants[restaurant]);

Cuisine &&delivered_food = delivery_man.delivery(restaurants[restaurant].make_cuisine(food_name),
                             restaurants[restaurant].location,
                             home);
```
손님이 주문을 할 때마다 이렇게 식당, 배달원, 배달 서비스 업체가 얽혀있는 번잡한 프로세스를 구현해야 할까?  
손님은 단순히 식당 이름, 음식 이름, 서비스 업체 이름, 집 주소만 알려주면 음식이 배달와야 한다.  
&nbsp;  

## 단순한 인터페이스  

퍼사드 패턴을 통해 식당, 배달원, 배달 서비스 업체의 복잡한 프로세스는 숨기고 단순한 인터페이스를 제공해보자.  
```c++
class OrderFacade
{
    std::vector<Restaurant> restaurants;
    std::vector<DeliveryMan> delivery_men;
    std::vector<OrderingService> services;

public:
    OrderFacade()
    {
        // 식당 초기화
        restaurants.push_back(Restaurant{
            "pizza town",
            {{"potato pizza", {"dough", "potato", "oil", "water", "salt"}}},
            {51.38f, 104.1f}});

        restaurants.push_back(Restaurant{
            "pasta mall",
            {{"tomato pasta", {"noodle", "tomato", "oil", "water", "sugar", "parsley"}}},
            {-20.5f, -77.22f}});

        // 배달원 초기화
        delivery_men.push_back(DeliveryMan{
            "Iron Man",
            {103.f, 58.76f}});

        delivery_men.push_back(DeliveryMan{
            "Captin America",
            {-42.f, 13.6f}});

        delivery_men.push_back(DeliveryMan{
            "Thor",
            {55.4f, 11.2f}});

        // 배달 서비스 초기화
        services.push_back(OrderingService{"BeaMin", restaurants, delivery_men});

        services.push_back(OrderingService{"Yogiyo", restaurants, delivery_men});
    }

    Cuisine &&order(std::string &&service_name, std::string &&restaurant_name, std::string &&food_name, std::pair<float, float> &&home)
    {
        auto restaurant = std::find_if(restaurants.begin(), restaurants.end(), [&](auto &r) -> bool
                                       { return restaurant_name == r.name; });

        auto service = std::find_if(services.begin(), services.end(), [&](auto &r) -> bool
                                    { return service_name == r.name; });

        DeliveryMan &delivery_man = service->matching(*restaurant);
        return delivery_man.delivery(restaurant->make_cuisine(food_name),
                                     restaurant->location,
                                     home);
    }
};
```
식당, 배달원, 배달 서비스 업체가 얽혀 진행되는 복잡한 프로세스는 모두 order() 함수 속에 숨겨져있다.  
&nbsp;  

사용자는 단순히 밑과 같이 주문만 하면 될 뿐이다.  
```c++
OrderFacade order_system;
Cuisine &&delivered_food = order_system.order("BeaMin", "pizza town", "potato pizza", {30.f, 1.f});
```
내부에서 진행되는 복잡한 과정은 알필요가 없다.  
&nbsp;  

order() 함수의 인자로 구조체를 넘기는 방식도 있다.  
```c++
struct OrderData
{
    std::string service_name{"BeaMin"};
    std::string restaurant_name{"pizza town"};
    std::string food_name{"potato pizza"};
    std::pair<float, float> home{30.f, 1.f};
};

Cuisine &&order(const OrderData &orderdata = OrderData())
{
    auto restaurant = std::find_if(restaurants.begin(), restaurants.end(), [&](auto &r) -> bool
                                   { return orderdata.restaurant_name == r.name; });

    auto service = std::find_if(services.begin(), services.end(), [&](auto &r) -> bool
                                { return orderdata.service_name == r.name; });
                                
    DeliveryMan &delivery_man = service->matching(*restaurant);
    return delivery_man.delivery(restaurant->make_cuisine(orderdata.food_name),
                                 restaurant->location,
                                 orderdata.home);
}
```
해당 방식의 장점은 각 인자들의 디폴트 값을 한 곳에서 관리하기 쉽다는 것이다.  
&nbsp;  

## 요약  

1. 퍼사드 패턴은 복잡한 라이브러리와 API, 서브 클래스들 사이의 통합 인터페이스를 제공할 때 용이하다.    

2. 퍼사드 패턴으로 제공한 인터페이스에 구조체를 이용해 인자를 넘기는 방식도 고려해보자.  