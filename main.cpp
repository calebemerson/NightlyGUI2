#include <SFML/OpenGL.hpp>
#include "TextureManager.h"
#include <iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<queue>
#include <stack> /////////////////////////////////////////////////////////////////BA
#include <unordered_set> ///////////////////////////////////////////////////////////////////BA
#include<algorithm>
#include <ctime>
#include <random>


class Party {
private:
    vector<int> attendees;
    int capacity;
public:
    Party(int cap) { capacity = cap; };
    vector<int> getAttendees();
    bool addAttendee(int person);
};

bool Party::addAttendee(int person) {
    if (attendees.size() >= capacity)
        return false;
    attendees.push_back(person);
    return true;
}

vector<int> Party::getAttendees() {
    return attendees;
}

class Graph
{
    struct Node {
        int event = -1;

        explicit Node(int id1) { event = -1; }
        void setEvent(int num) { event = num; }

    };
private:
    unordered_map<int, vector<int>> friendMap;
    unordered_map<int, Node*> eventMap;
    vector<Party> ongoingEvents;
public:
    Graph();
    void insertEdge(int from, int to);
    int getEvent(int person);
    void assignEvent(int person);
    vector<int> getFriends(int vertex);
    vector<Party> getEvents();
    bool isEdge(int from, int to);
    void DFS(int src); /////////////////////////////////////////////////////////////////////////////////BA
};

Graph::Graph() {
    // initialize number of events- the actual attendees will be assigned via level order traversal
    // potentially read csv file here
    Party poolParty = Party(15);
    ongoingEvents.push_back(poolParty);
    Party starGazing = Party(10);
    ongoingEvents.push_back(starGazing);
    Party dogPark = Party(20);
    ongoingEvents.push_back(dogPark);
    Party studySession = Party(10);
    ongoingEvents.push_back(studySession);
    Party mineCraft = Party(30);
    ongoingEvents.push_back(mineCraft);


}

void Graph::insertEdge(int from, int to)
{
    if (eventMap.find(from) == eventMap.end()) {
        Node* temp = new Node(from);
        eventMap[from] = temp;
    }
    if (eventMap.find(to) == eventMap.end()) {
        Node* temp = new Node(to);
        eventMap[to] = temp;
    }
    friendMap[from].push_back(to);
    friendMap[to].push_back(from);

}

bool Graph::isEdge(int from, int to) {
    vector<int> edges = friendMap[to];
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i] == to)
            return true;
    }
    return false;
}

int Graph::getEvent(int person) { return eventMap[person]->event; }

vector<Party> Graph::getEvents() {
    return ongoingEvents;
}

void Graph::assignEvent(int person) {
    // assign random number within our range
    // adds attendee to that event
    // if successful, assigns node to that event number
    // else, assign node to 0 event number (node was visited, but not assigned event)
    int num = rand() % 5;
    bool success = ongoingEvents[num].addAttendee(person);
    if (success)
        eventMap[person]->setEvent(num+1);
    else
        eventMap[person]->setEvent(0);

}

vector<int> Graph::getFriends(int vertex)
{
    return friendMap[vertex];
}

//Bennett's DFS
void Graph::DFS(int src) {
    stack<int> stk;
    unordered_set<int> visited;
    stk.push(src);
    int count = 0;

    while (!stk.empty() && count < 50) {

        int person = stk.top();
        if (visited.find(person) == visited.end()) {
            cout << person << endl;
            count++;
        }
        stk.pop();
        visited.insert(person);

        for (int i = 0; i < friendMap[person].size(); i++) {
            if (visited.find(friendMap[person][i]) == visited.end()) {
                stk.push(friendMap[person][i]);
            }
        }
    }

}

void LoadEdges(const string& filePath, Graph& graph) //////////////////////////////////////////////////////////////BA
{
    ifstream infile(filePath);

    if (infile.is_open()) {

        string thisLine;

        while (getline(infile, thisLine))
        {
            istringstream stream(thisLine);

            string tempID1, tempID2;
            int id1, id2;

            getline(stream, tempID1, ',');
            id1 = stoi(tempID1);
            getline(stream, tempID2);
            id2 = stoi(tempID2);

            graph.insertEdge(id1, id2);
        }
    }
    else {
        cout << "ugh" << endl;
    }
}

void LevelOrderTraversal(int userNode, Graph& graph) {
    queue<int> q;
    q.push(userNode);
    q.push(0); // 0 indicates the end of a level;
    int levels = 0;

    while(!q.empty() && levels < 5) { // 10 is arbitrary number

        int person = q.front();
        q.pop();

        if (person == 0 && !q.empty()) {
            levels++;
            q.push(0);
        }

        vector<int> friends = graph.getFriends(person);
        for (int & i : friends) {
            if (graph.getEvent(i) == -1) {
                graph.assignEvent(i);
                q.push(i);
            }
        }
    }
}

vector<int> findFriends(int userNode, Graph& graph) {
    // I am making four events for now, we can decide what number works best later
    int poolParty = 0;
    int starGazing = 0;
    int dogPark = 0;
    int studySession = 0;
    int mineCraft = 0;
    vector<int> friends = graph.getFriends(userNode);
    for (int i = 0; i < friends.size(); i++) {
        if (graph.getEvent(friends[i]) == 0)
            continue;
        else if (graph.getEvent(friends[i]) == 1)
            poolParty++;
        else if (graph.getEvent(friends[i]) == 2)
            starGazing++;
        else if (graph.getEvent(friends[i]) == 3)
            dogPark++;
        else if (graph.getEvent(friends[i]) == 4)
            studySession++;
        else if (graph.getEvent(friends[i]) == 5)
            mineCraft++;
    }

    // decide what we want to do with this information/ want return values to be
    return {poolParty,starGazing,dogPark,studySession,mineCraft};
}

vector<int> makeFriends(int userNode, Graph& graph) {
    int event = graph.getEvent(userNode);
    vector<Party> curr = graph.getEvents();
    vector<int> people = curr[event-1].getAttendees();
    vector<int> added;

    for (int i = 0; i < people.size(); i++) {
        if (!graph.isEdge(userNode,people[i])) {
            graph.insertEdge(userNode,people[i]);
            added.push_back(people[i]);
        }
    }
    return added;
}

int main() {

    Graph myGraph;
    LoadEdges("C:/Users/wofar/CLionProjects/NightlyGUI/edges.csv", myGraph);
    LevelOrderTraversal(10000, myGraph);
    vector<int> friends = findFriends(10000, myGraph);
    myGraph.DFS(10000);

    int top = 0;              // calculate top three events
    int topj = 0;
    vector<int> topThreeEvents;
    vector<int> friends2 = friends;

    for (int i = 0; i < friends.size(); i++) {
        friends2.push_back(friends[i]);
    }

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < friends.size(); j++) {

            if (friends2[j] > top) {
                top = friends2[j];
                topj = j;
            }
        }
        friends2[topj] = 0;
        topThreeEvents.push_back(topj);
        topj = 0;
        top = 0;
    }




    RenderWindow window(VideoMode( 500, 896), "UserView");   // screen size is 2/3 resolution of iphone 6 screen

    bool findFriend = false;
    bool welcome = true;
    bool eventView = false;
    bool newFriends = false;
    int nextEvent = 1;

    TextureManager textures;
    textures.LoadTexture("Nightly logo");
    textures.LoadTexture("findFriends");
    textures.LoadTexture("doBase");
    textures.LoadTexture("dog park");
    textures.LoadTexture("Minecraft");
    textures.LoadTexture("poolParty");
    textures.LoadTexture("starGazing");
    textures.LoadTexture("study session");
    textures.LoadTexture("crescentMoon");
    textures.LoadTexture("boring");
    textures.LoadTexture("makeFriends");
    Font font;
    font.loadFromFile("srcImg/OpenSans-Regular.ttf");


    while (window.isOpen()) {      // currently infinite window


        Event event;

        while (window.pollEvent(event)){

            if (event.type == Event::Closed){
                window.close();
            }

            if (welcome) {

                Sprite sprite;
                sprite.setTexture(textures.GetTexture("NightlyWelcome"));
                sprite.setPosition(0.0f, 0.0f);
                window.draw(sprite);

                if (Mouse::isButtonPressed(Mouse::Left)){
                    findFriend = true;
                    welcome = false;
                }

                window.display();
            }
            else if (findFriend){

                window.clear();
                Sprite doBase;
                doBase.setTexture(textures.GetTexture("doBase"));
                doBase.setPosition(0.0f, 0.0f);
                window.draw(doBase);

                Sprite events1;
                Sprite events2;
                Sprite events3;

                events1.setTexture(textures.GetTexture("crescentMoon"));
                events2.setTexture(textures.GetTexture("crescentMoon"));
                events3.setTexture(textures.GetTexture("crescentMoon"));

                for (int i = 1; i < 4; i++) {
                    Text text;
                    text.setFont(font);
                    text.setCharacterSize(30);
                    text.setOutlineColor(Color::White);
                    text.setFillColor(Color::White);
                    text.setPosition(20.0f, 150.0f + (i*150)*1.0f);
                    string temp;
                    string eventName;
                    string friendsThere;

                    // set nextEvent based on ranking from graph algorithm

                    switch (topThreeEvents[i - 1]) {                  // sets event name based on a 1 through 5 identification system
                        case 1:
                            eventName = "Pool Party";
                            break;
                        case 2:
                            eventName = "Stargazing";
                            break;
                        case 3:
                            eventName = "Dog Park Gathering";
                            break;
                        case 4:
                            eventName = "Study Session";
                            break;
                        case 5:
                            eventName = "Minecraft Meeting";
                            break;
                    }
                    temp = (char) (i + 48);
                    friendsThere = (char) (friends[topThreeEvents[i - 1]] + 48);
                    text.setString(temp + ". " + eventName + "    F: " + friendsThere);
                    window.draw(text);
                }

                events1.setPosition(420.0f, 300.0f);
                window.draw(events1);
                events2.setPosition(420.0f, 450.0f);
                window.draw(events2);
                events3.setPosition(420.0f, 600.0f);
                window.draw(events3);



                window.display();

                if (Mouse::isButtonPressed(Mouse::Right)) {

                        welcome = true;
                        newFriends = false;


                }

                if (Mouse::isButtonPressed(Mouse::Left)){
                    if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events1.getPosition().y && Mouse::getPosition(window).y < events1.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;
                        nextEvent = topThreeEvents[0];

                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events2.getPosition().y && Mouse::getPosition(window).y < events2.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;
                        nextEvent = topThreeEvents[1];
                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > events1.getPosition().x && Mouse::getPosition(window).x < events1.getPosition().x + 80.0f && Mouse::getPosition(window).y > events3.getPosition().y && Mouse::getPosition(window).y < events3.getPosition().y + 50.0f) {
                        eventView = true;
                        findFriend = false;
                        nextEvent = topThreeEvents[2];
                        // nextEvent = third ranked
                        // set nextEvent according to clicked sprite
                    }
                }

            }
            else if (eventView) {

                window.clear();
                Sprite eventPicture;
                Sprite boring;
                Sprite makeFriends;



                switch (nextEvent) {                  // sets event name based on a 1 through 5 identification system
                    case 1:
                        eventPicture.setTexture(textures.GetTexture("poolParty"));
                        break;
                    case 2:
                        eventPicture.setTexture(textures.GetTexture("starGazing"));
                        break;
                    case 3:
                        eventPicture.setTexture(textures.GetTexture("dog park"));
                        break;
                    case 4:
                        eventPicture.setTexture(textures.GetTexture("study session"));
                        break;
                    case 5:
                        eventPicture.setTexture(textures.GetTexture("Minecraft"));
                        break;
                }

                boring.setTexture(textures.GetTexture("boring"));
                boring.setPosition(50.0f, 600.0f);
                window.draw(boring);

                makeFriends.setTexture(textures.GetTexture("makeFriends"));
                makeFriends.setPosition(300.0f, 600.0f);
                window.draw(makeFriends);

                eventPicture.setPosition(60.0f, 100.0f);
                window.draw(eventPicture);
                window.display();

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (Mouse::getPosition(window).x > boring.getPosition().x &&
                        Mouse::getPosition(window).x < boring.getPosition().x + 100.0f &&
                        Mouse::getPosition(window).y > boring.getPosition().y &&
                        Mouse::getPosition(window).y < boring.getPosition().y + 100.0f) {
                        eventView = false;
                        findFriend = true;

                        // set nextEvent according to clicked sprite
                    }
                    else if (Mouse::getPosition(window).x > makeFriends.getPosition().x &&
                             Mouse::getPosition(window).x < makeFriends.getPosition().x + 100.0f &&
                             Mouse::getPosition(window).y > makeFriends.getPosition().y &&
                             Mouse::getPosition(window).y < makeFriends.getPosition().y + 100.0f) {

                        eventView = false;
                        newFriends = true;

                    }
                }

                /*if (Mouse::isButtonPressed(Mouse::Left)){
                    findFriend = true;
                    welcome = false;
                }*/
            }
            else if (newFriends) {
                window.clear();
                int userId = 0;

                Sprite boring;
                boring.setTexture(textures.GetTexture("boring"));
                boring.setPosition(25.0f, 750.0f);
                window.draw(boring);

                Text text;
                text.setFont(font);
                text.setCharacterSize(90);
                text.setOutlineColor(Color::White);
                text.setFillColor(Color::White);

                text.setString("Hooray!");
                text.setPosition( 50.0f, 50.0f);
                window.draw(text);

                text.setCharacterSize(50);
                text.setString("New Friends:");
                text.setPosition( 50.0f, 200.0f);
                window.draw(text);

                // int to string to display user id
                string user = to_string(userId);
                vector<int> friendsMade = makeFriends(10000, myGraph);

                for (int i = 1; i < friendsMade.size(); i++) {                    // 4 needs to be set to number of friends made

                    text.setCharacterSize(30);              // display friends just made
                    text.setPosition(20.0f, 300.0f + (i*50)*1.0f);
                    string temp;
                    string eventName;
                    string friendsThere;


                    temp = (char) (i + 48);
                    string user = to_string(friendsMade[i - 1]);
                    text.setString(temp + ". " + user);
                    window.draw(text);
                }

                window.display();

                if (Mouse::isButtonPressed(Mouse::Left)) {
                    if (Mouse::getPosition(window).x > boring.getPosition().x &&
                        Mouse::getPosition(window).x < boring.getPosition().x + 100.0f &&
                        Mouse::getPosition(window).y > boring.getPosition().y &&
                        Mouse::getPosition(window).y < boring.getPosition().y + 100.0f) {
                        newFriends = false;
                        findFriend = true;

                    }
                }
            }

        }

    }

    return 0;
}
