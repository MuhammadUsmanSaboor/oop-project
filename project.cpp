
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Page;
class Char;
class SocialNetwork;
class User;
class Post;
class Memory;

class Element {
public:

    virtual Char* getID() const = 0;
    virtual Char* getName() const = 0;
    virtual void addPost(Post*) {};
    virtual ~Element() {};

};


class Char {

private:

    char* Strings;
    int length;

public:

    int getBufferLength() { return this->length; }
    char* getString() {
        return this->Strings;
    }
    
    void DisplayString() {

        cout << Strings << endl;
    }
    Char ReadFromFile(ifstream& iFile) {
        char temp[2000];
        iFile >> temp;
        return Char(temp);
    }

    void setString(const char* str) {
        if (Strings != nullptr) {
            delete[] Strings;
        }
        length = getLength(str) + 1;
        Strings = new char[length];
        int i = 0;
        while(i < getLength(str)) {
            Strings[i] = str[i];
            i++;
        }

        Strings[i] = '\0';
    
    }

    int getLength(const char* checker)
    {

        int index = 0;
        for (int i = 0; checker[i] != '\0'; i++) {
            index++;
        }
        return index;
    
    }
    
    Char(const char* setter)
    {

        this->length = getLength(setter) + 1;
        this->Strings = new char[length];
        int i = 0;
        for (; i < getLength(setter); i++) {
            Strings[i] = setter[i];
        }
        Strings[i] = '\0';
  
    }

    ~Char() {

        delete[] this->Strings;
        Strings = nullptr;
        length = 0;
    
    }

    void concatenate(const char* src) {
        // takes len of concater and make a temp pointer, copy old into new one and then append and then updating pointer and length
        int conc_length = getLength(src);
        char* temp = new char[conc_length + this->length];
        // Localcopy(temp,buffer);
        int i = 0;
        for (; Strings[i] != '\0'; i++) {
            temp[i] = Strings[i];
        }
        for (int j = 0; j < conc_length; j++, i++) {
            temp[i] = src[j];
        }
        temp[i] = '\0';
        delete[] Strings;
        Strings = temp;
        length += conc_length + 1;
        
    }


    Char() {
        this->Strings = nullptr;
        length = 0;
    }

    bool compare(Char rhs) {
        if (this->length != rhs.length) {
            return false;
        }
        else {
            for (int i = 0; Strings[i] != '\0'; i++) {
                if (rhs.Strings[i] != this->Strings[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    bool compare(const char* rhs) {
        cout << getLength(rhs) << "  " << this->length;
        cout << rhs << "  " << this->Strings;
        if (this->length != getLength(rhs)) {
            return false;
        }
        else {
            for (int i = 0; Strings[i] != '\0'; i++) {
                if (rhs[i] != this->Strings[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    bool strcmp(const char* t1, const char* t2) {
        if (getLength(t1) != getLength(t2)) {
            return false;
        }
        else {
            for (int i = 0; i < getLength(t1); i++) {
                if (t1[i] != t2[i]) {
                    return false;
                }
            }
            return true;
        }
    }

    friend ostream& operator<<(ostream& print, Char* value) {
        print << value->getString();
        return print;
    }

};


class Date {
private:

    int day, month, year;

public:


    const char* getStringForm() {

        static char dateString[12]; // Assuming max size is 11 characters ("DD/MM/YYYY\0")
        sprintf_s(dateString, "%02d/%02d/%04d", day, month, year);
        return dateString;
   
    }



    void setDate(int d, int m, int y) {

        if (d < 31) {
            this->day = d;
        }
        else {
            this->day = 31; // maximum date possible just for fun
        }
        if (m < 12) {
            this->month = m; // maximum month
        }
        else {
            this->month = 12;
        }
        this->year = y;
    }

   

    Date(int d=12, int m=5, int y=2024) {
        if (d < 31) {
            this->day = d;
        }
        else {
            this->day = 31; // maximum date possible just for fun
        }
        if (m < 12) {
            this->month = m; // maximum month
        }
        else {
            this->month = 12;
        }
        this->year = y;
    }

    void ViewDate() {
        cout << day << "/" << month << "/" << year;
    }

    void setDay(int d) 
    {
        if (d < 31) {
            this->day = d;
        }
        else {
            this->day = 31; // maximum date possible just for fun
        }
    }

    void DisplayFormatted() 
    {

        if (month=CurrentDate.month && year == CurrentDate.year && (CurrentDate.day - day) < 1)
            cout << "1hr ago";
        else if (month == CurrentDate.month && year == CurrentDate.year && (CurrentDate.day - day) < 2)
            cout << "1 day ago";
        else if (month == CurrentDate.month && year == CurrentDate.year && (CurrentDate.day - day) < 3)
            cout << "2 days ago";
        else if (month == CurrentDate.month && year == CurrentDate.year && (CurrentDate.day - day) < 4)
            cout << "3 days ago";
        else
            cout << day << "/" << month << "/" << year;

    }

    void setYear(int y) { this->year = y; }

    void setMonth(int m) {
        if (m < 12) {
            this->month = m; // maximum month
        }
        else {
            this->month = 12;
        }
    }
    int getMonth() { return this->month; }
    int getDay() { return this->day; }
    int getYear() { return this->year; }

    int compareDate(Date rhsDate) {
        // treating a month as 30 days on average and a year as 365 days
        int lhsDayCount, rhsDayCount = 0;
        lhsDayCount = (this->year) * 365 + (this->month) * 30 + day;
        rhsDayCount = (rhsDate.year) * 365 + (rhsDate.month) * 30 + rhsDate.day;
        return lhsDayCount - rhsDayCount;
    }
    static Date CurrentDate;
};

Date Date::CurrentDate;


class Page : public Char, public Element {
private:
    Char* ID;
    //User* owner;
    Char* title;
    int noOfFollowers;
    int noOfPosts;
    User** followers;
    Post** posts;
public:
    
    Page(const char* id, const char* name) {
        this->ID = new Char(id);
        this->title = new Char(name);
    }

    void addFollower(User*);

    Char* getID() const override { return this->ID; }
    Char* getName() const override { return this->title; }
    int getFollowersCount() { return this->noOfFollowers; }
    User** getFollowers() { return this->followers; }
    void addPost(Post* newPost) override;
    Post** getPosts() { return this->posts; }
    int getPostCount() { return this->noOfPosts; }
    void printPage();

};



void Page::addPost(Post* newPost) {
    Post** tempPosts = new Post * [noOfPosts + 1];
    int i = 0;
    for (; i < noOfPosts; i++) {
        tempPosts[i] = posts[i];
    }
    delete[] posts;
    tempPosts[i] = newPost;
    posts = tempPosts;
    noOfPosts++;
}


void Page::addFollower(User* NewFllr) {
    User** tempFollowers = new User * [noOfFollowers + 1];
    int i = 0;
    for (; i < noOfFollowers; i++) {
        tempFollowers[i] = followers[i];
    }
    delete[] followers;
    tempFollowers[i] = NewFllr;
    followers = tempFollowers;
    noOfFollowers++;
}




class User : public Element {
private:

    Char* ID;
    Char* Name;
    User** friendsList;
    int noOfFriends;
    int noOfLikedPages;
    Page** LikedPages;
    Post** posts;
    int totalPosts;

public:
    ~User();

    // constructors
    User(const char* id, const char* f_name, const char* l_name);
    User(const char*, const char*);
    User();


    // adders
    void DisplayName(){cout<<Name->getString()<<endl;}
    void addPage(Page* NewPage);
    void addPost(Post*) override;
    void addFriend(User*);

    //viewers
    void viewFriendList();
    void viewLikedPages();

    //getters
    Page** getLikedPages() { return this->LikedPages; }
    int getLikedPagesCount() { return this->noOfLikedPages; }
    Post** getPosts() { return this->posts; }
    int getPostCount() { return this->totalPosts; }
    Char* getID() const override { return this->ID; }
    Char* getName() const override { return this->Name; }
    User** getFriendList() { return this->friendsList; }
    int getFriendsNumber() { return this->noOfFriends; }
    void ViewMemory();

};

void User::addPage(Page* NewPage) {
    Page** tempPages = new Page * [noOfLikedPages + 1];
    int i = 0;
    for (; i < noOfLikedPages; i++) {
        tempPages[i] = LikedPages[i];
    }
    delete[] LikedPages;
    tempPages[i] = NewPage;
    LikedPages = tempPages;
    noOfLikedPages++;
};
//
void User::ViewMemory() 
{
  /*  cout << "We hope you Enjoy Looking Back to your Previous Memory" << endl;
    
        for (int i = 0; i < totalPosts; i++)
        {
                if (posts[i]->IsSharedDaySame()) {
                    posts[i]->viewPost();
                }
            
        }*/
   
}

void User::addPost(Post* newPost) 
{

    Post** tempPosts = new Post * [totalPosts + 1];
    int i = 0;
    for (; i < totalPosts; i++) {
        tempPosts[i] = posts[i];
    }
    delete[] posts;
    tempPosts[i] = newPost;
    posts = tempPosts;
    totalPosts++;

};

void User::viewLikedPages() {
    cout << endl << Name->getString() << " - Liked Pages" << endl;
    for (int i = 0; i < noOfLikedPages; i++) {
        
        if (LikedPages[i]) {
            cout << LikedPages[i]->getID()->getString() << " - " << LikedPages[i]->getName()->getString() << endl;
        }
    }
};

void User::viewFriendList() {
    cout << endl << this->Name->getString() << " - Friend List" << endl;
    for (int i = 0; i < noOfFriends; i++) {
        cout << friendsList[i]->getID()->getString() << " - " << friendsList[i]->getName()->getString() << endl;
    }
};


User::User() {

    posts = new Post * [1];
    posts[0] = nullptr;
    ID = Name = nullptr;
    friendsList = nullptr;
    noOfFriends = 0;
    noOfLikedPages = 0;
    LikedPages = nullptr;
}

User::User(const char* id, const char* f_name, const char* l_name) {

    this->posts = new Post * [1];
    posts[0] = nullptr;
    this->ID = new Char(id);
    this->Name = new Char(f_name);
    this->Name->concatenate(" ");
    this->Name->concatenate(l_name);
    this->noOfFriends = this->noOfLikedPages = 0;
    this->friendsList = nullptr;
    this->LikedPages = nullptr;
}


User::User(const char* id, const char* Name) {
    this->ID = new Char(id);
    this->Name = new Char(Name);
    this->noOfFriends = this->noOfLikedPages = 0;
    this->friendsList = nullptr;
    this->LikedPages = nullptr;
}



void User::addFriend(User* NewFrnd) 
{

    if (noOfFriends < 10) {
        User** tempFriends = new User * [noOfFriends + 1];
        int i = 0;
        for (; i < noOfFriends; i++) {
            tempFriends[i] = friendsList[i];
        }
        delete[] friendsList;
        tempFriends[i] = NewFrnd;
        friendsList = tempFriends;
        noOfFriends++;
    }
}

User::~User() {


    /*for (int i = 0; i < noOfFriends; i++) {
        delete friendsList[i];
    }
    delete[] friendsList;*/
}


class Activity {
private:
    Char* activity;
    int type;
    const char* mapping[4] = { "Feeling","Thinking about","Making","Celebrating" };
public:
    Activity(const char*, int);
    ~Activity();

    int getType() { return this->type; }
    Char* getActivity() { return this->activity; }

    void setType(int Ptype) { this->type = Ptype; }
    void setActivity(const char*);
    const char* mapType(int);
    // void printActivity();
    friend ostream& operator<<(ostream&, Activity);

};

ostream& operator<<(ostream& print, Activity* act) {
    print << "is " << act->mapType(act->getType()) << act->getActivity();
    return print;
}

const char* Activity::mapType(int type) {
    return this->mapping[type - 1];
};

Activity::~Activity() {
    delete this->activity;
};

void Activity::setActivity(const char* provided_value) {
    delete this->activity;
    this->activity = new Char(provided_value);
};

Activity::Activity(const char* provided_activity, int provided_type) {
    this->activity = new Char(provided_activity);
    this->type = provided_type;
};



class Comment : public Char {
private:
    Char* ID;
    Char* content;
    Element* owner;
    Post* parent;
public:
    Comment(const char*, const char*);
    Comment(const char*, const char*, Element*, Post*);

    // getters
    Char* getID() { return this->ID; }
    Char* getConent() { return this->content; }
    Element* getOwner() { return this->owner; }
    Post* getParentPost() { return this->parent; }

    // setters
    void setOwner(Element* newOnwer) { this->owner = newOnwer; }
    void setParentPost(Post* prnt_post) { this->parent = prnt_post; }
};

Comment::Comment(const char* id, const char* cmnt) {
    this->ID = new Char(id);
    this->content = new Char(cmnt);
    owner = nullptr;
    parent = nullptr;
}

Comment::Comment(const char* id, const char* cmnt, Element* p_owner, Post* prnt) {
    this->ID = new Char(id);
    this->content = new Char(cmnt);
    //cout << cmnt << String::getLength(cmnt) << endl;
    //cout << this->content->getBufferLength() << endl;
    owner = p_owner;
    parent = prnt;
}


class Post {
private:

    Char* ID;
    Char* content;
    int LikesCount;
    Element** Likes;
    Date SharingDate;
    Comment** comments;
    int totalComments;
    Element* owner;
    Activity* activity;

public:

    Post();
    Post(const char*, const char*, int, int, int, Element*, int, const char*);
    ~Post();

    void PrintSharedDate() { SharingDate.DisplayFormatted(); }

    void viewPost();

    int getLikesCount() { return this->LikesCount; }
    int getCommentsCount() { return this->totalComments; }
    Char* getID() { return this->ID; }
    Char* getContent() { return this->content; }
    Element** getLikedByList() { return this->Likes; }
    Date getSharingDate() { return this->SharingDate; }
    Comment** getComments() { return this->comments; }
    Element* getOwner() { return this->owner; }
    Activity* getActivity() { return this->activity; }
    bool IsSharedDaySame();
    // setters
    void PrintSharedBy() { owner->getID()->DisplayString(); }
    void LikePost(Element*);
    void AddComment(Comment*);

};

Post::Post() {

    ID = nullptr;
    content = nullptr;
    LikesCount = 0;
    Likes = new Element * [1];
    Likes[0] = nullptr;
    comments = new Comment * [1];
    comments[0] = nullptr;
    totalComments = 0;
    this->owner = nullptr;
    activity = nullptr;


}

bool Post::IsSharedDaySame()
{

    if (SharingDate.getDay() == Date::CurrentDate.getDay() &&
        SharingDate.getMonth() == Date::CurrentDate.getMonth() &&
        (Date::CurrentDate.getYear() - SharingDate.getYear()) >= 1)
    {

        cout << "On this day" << endl
            << Date::CurrentDate.getYear() - SharingDate.getYear() << " Years Ago." << endl;
        return true;
    }
    return false;
}

void Post::LikePost(Element* tempLiker) 
{

    Element** tempFriends = new Element * [LikesCount + 1];
    int i = 0;
    for (; i < LikesCount; i++) {
        tempFriends[i] = Likes[i];
    }
    delete[] Likes;
    tempFriends[i] = tempLiker;
    Likes = tempFriends;
    LikesCount++;
}

void Post::viewPost() 
{

    cout << "- " << this->owner->getName() << " ";
    if (this->activity != nullptr) {
        cout << this->activity << endl;
    }
    else {
        cout << "shared ";
    }
    cout << "\"" << this->content << "\"    ....(";
    this->getSharingDate().ViewDate();
    cout << ") " << endl;
    for (int i = 0; i < totalComments; i++) {
        cout << "\t" << comments[i]->getOwner()->getName()->getString() << " wrote: " << "\"" << comments[i]->getConent() << "\"" << endl;
    }

}


void Post::AddComment(Comment* tempComment) {
    if (totalComments < 10) {
        Comment** tempComments = new Comment * [totalComments + 1];
        int i = 0;
        for (; i < totalComments; i++) {
            tempComments[i] = comments[i];
        }
        delete[] comments;
        tempComments[i] = tempComment;
        comments = tempComments;
        totalComments++;
    }
    else {
        cout << "Max comments reached on " << tempComment->getConent() << endl;
        delete tempComment;
        tempComment = nullptr;
    }

}


Post::Post(const char* id, const char* description, int d, int m, int y, Element* POwner, int activity_type, const char* activity_value) {
    
    this->ID = new Char(id);
    this->content = new Char(description);
    this->SharingDate = Date(d, m, y);
    LikesCount = totalComments = 0;
    Likes = nullptr;
    //cout << "performing polymorphization" << endl;
    this->owner = POwner;
    comments = nullptr;
    //cout << "Done" << endl;
    if (activity_type != -1) {
        this->activity = new Activity(activity_value, activity_type);
    }
    else {
        this->activity = nullptr;
    }
};


Post::~Post() {
    delete ID;
    delete content;
    delete activity;
    owner = nullptr;
    delete comments;
    comments = nullptr;
    delete Likes;
    Likes = nullptr;
    totalComments = LikesCount = 0;

};
void Page::printPage() {
    cout << endl << this->title << endl;
    for (int i = 0; i < noOfPosts; i++) {
        if (posts[i]) {
            posts[i]->viewPost();
        }
    }
}

class Memory : public Post,public Char
{
private: 

    Char* content;
    Date sharedDate;
    User* owner;
    Post* ReferencePost;

public:

    Memory(const char*,Date, Post*,User* ); 

    ~Memory() {
    
        delete this->content;
        content = nullptr;
        owner = nullptr;
        ReferencePost = nullptr;
    
    }

    void DisplayMemory();

};
Memory::Memory(const char* Caption, Date TempDate, Post*ref , User* temp)
{
    this->content = new Char(Caption);
    this->sharedDate.setDate(TempDate.getDay(), TempDate.getMonth(), TempDate.getYear());
    this->ReferencePost = ref;
    this->owner - temp;
}

void Memory::DisplayMemory() 
{
    string temp;
    cout << "~~" << this->owner->getName() << "Memory Was shared----------..." << sharedDate.getStringForm() << endl;
    cout << content->getString() << endl;
    cout << sharedDate.compareDate(this->ReferencePost->getSharingDate()) / 365;
    cout << "Year ago)";
    temp = "--";
    temp += this->owner->getName()->getString();
    temp += "Memory was shared --------...";
    temp += sharedDate.getStringForm();
    temp += "\n";
    temp += content->getString();
    temp += "\n\t (";
    temp += to_string(sharedDate.compareDate(this->ReferencePost->getSharingDate()) / 365);
    temp += " Years Ago)";
   // temp += ReferencePost->viewPost();
  //  return temp;

} 


class SocialNetwork : public Char {
private:

    User* CurrentUser;
    Date CurrentDate;
    int TotalUsers;
    User** socialUsers;
    int totalPages;
    Page** Social_Pages;
    int totalPosts;
    Post** Social_Posts;
    int totalComments;
    Comment** socialComments;
    int totalNoofMemories;
    Memory** memories;


public:

    SocialNetwork();
    ~SocialNetwork();


    // setters
    void setTime(int, int, int);
    void setCurrentUser(const char*);

    // Load Data
    void LoadApp();
    void InputUser(const char*);
    void InputPages(const char*);
    void InputPosts(const char*);
    void InputComments(const char*);
    void ShareMemory(const char*,const char*);
    void runApp();
    void PrintHome();
    void viewTimeline();
    void viewLikedList(const char*);
    void likePost(const char*);
    void viewPost(const char*);
    void viewPage(const char*);
    

    void postComment(const char*, const char*);
    void createUser(const char*, const char*);
    void createPage(const char*, const char*);
    

    // functions
    User* searchUser(const char*);
    Page* searchPage(const char*);
    Post* searchPost(const char*);
};

void SocialNetwork::viewPage(const char* pageID) {
    searchPage(pageID)->printPage();
}

void SocialNetwork::ShareMemory(const char* postID, const char* desc) {

    if (searchPost(postID)) {
        Memory* temp = new Memory(desc,CurrentDate,searchPost(postID),  CurrentUser);

        Memory** tempPtr = new Memory * [totalNoofMemories + 1];
        for (int i = 0; i < totalNoofMemories; i++) {
            tempPtr[i] = memories[i];
        }
        tempPtr[totalNoofMemories] = temp;
        totalNoofMemories++;
        delete[] memories;
        memories = tempPtr;
    }
}

void SocialNetwork::createPage(const char* pageID, const char* title) {
    if (searchPage(pageID) == nullptr) {
        Page** tempPages = new Page * [totalPages + 1];
        int i = 0;
        for (; i < totalPages; i++) {
            tempPages[i] = Social_Pages[i];
        }
        delete[] Social_Pages;
        tempPages[i] = new Page(pageID, title);
        Social_Pages = tempPages;
        totalPages++;
    }
    else {
        cout << endl << "A page with id \"" << pageID << "\" already exists!!" << endl;
    }
}


void SocialNetwork::createUser(const char* userID, const char* Name) {
    if (searchUser(userID) == nullptr) {
        User** tempUsers = new User * [TotalUsers + 1];
        int i = 0;
        for (; i < TotalUsers; i++) {
            tempUsers[i] = socialUsers[i];
        }
        delete[] socialUsers;
        tempUsers[i] = new User(userID, Name);
        socialUsers = tempUsers;
        TotalUsers++;
    }
    else {
        cout << endl << "A user with id \"" << userID << "\" already exists!!" << endl;
    }
}

void SocialNetwork::viewPost(const char* postID) {
    Post* target_post = searchPost(postID);
    target_post->viewPost();
}

void SocialNetwork::postComment(const char* postID, const char* content) {
    Post* target_post = searchPost(postID);
    Comment** tempComments = new Comment * [totalComments + 1];
    int i = 0;
    for (; i < totalComments; i++) {
        tempComments[i] = socialComments[i];
    }
    delete[] socialComments;
    tempComments[i] = new Comment("tempComment", content, CurrentUser, target_post);
    socialComments = tempComments;
    totalComments++;
    target_post->AddComment(tempComments[i]);
    //        cout << "Maximum comment reached on " << postID << endl;

}

void SocialNetwork::likePost(const char* postID) {
    Post* target_post = searchPost(postID);
    target_post->LikePost(CurrentUser);
}

void SocialNetwork::viewLikedList(const char* postID) 
{
    Post* target_post = searchPost(postID);
    if (target_post) {
        cout << endl << "Post Liked By: " << endl;
        Element** elem = target_post->getLikedByList();
        for (int i = 0; i < target_post->getLikesCount(); i++) {
            cout << elem[i]->getID() << " - " << elem[i]->getName() << endl;
        }
    }
    else {
        cout << endl << "No post with id " << postID << endl;
    }

}

void SocialNetwork::viewTimeline()
{
    cout << endl << CurrentUser->getName() << " -- TimeLine" << endl;
    Post** p = CurrentUser->getPosts();
    for (int i = 0; i < CurrentUser->getPostCount(); i++) {
        p[i]->viewPost();
        cout << endl;
    }
}
void SocialNetwork::PrintHome() {

    cout << endl;
    User** tempFriendsPtr = CurrentUser->getFriendList();
    Page** tempPages = CurrentUser->getLikedPages();
    Post** posts;
    for (int i = 0; i < CurrentUser->getFriendsNumber(); i++) {
        posts = tempFriendsPtr[i]->getPosts();
        for (int j = 0; j < tempFriendsPtr[i]->getPostCount(); j++) {
            posts[j]->viewPost();
        }
    }
    for (int i = 0; i < CurrentUser->getLikedPagesCount(); i++) {
        posts = tempPages[i]->getPosts();
        for (int j = 0; j < tempPages[i]->getPostCount(); j++) {
            posts[j]->viewPost();
        }
    }
   
}

void SocialNetwork::setCurrentUser(const char* usrID) 
{

    this->CurrentUser = searchUser(usrID);
    //    this->currentUser = usr;

}

User* SocialNetwork::searchUser(const char* ID) 
{

    for (int i = 0; i < TotalUsers; i++) {
        if (Char::strcmp(socialUsers[i]->getID()->getString(), ID)) {
            return socialUsers[i];
        }
    }
    return nullptr;
}

Page* SocialNetwork::searchPage(const char* ID) {
    for (int i = 0; i < totalPages; i++) {
        if (Char::strcmp(Social_Pages[i]->getID()->getString(), ID)) {
            return Social_Pages[i];
        }
    }
    return nullptr;
}
Post* SocialNetwork::searchPost(const char* ID) {
    cout << endl;
    for (int i = 0; i < totalPosts; i++) {
        if (Char::strcmp(Social_Posts[i]->getID()->getString(), ID)) {
            return Social_Posts[i];
        }
    }
    return nullptr;
}

void SocialNetwork::InputComments(const char* filename) {
    ifstream iFile(filename);
    if (!iFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    iFile >> totalComments;
    socialComments = new Comment * [totalComments];
    char id[10], post_id[10], owner_id[10], content[500];
    for (int i = 0; i < totalComments; i++) {
        iFile >> id >> post_id >> owner_id;
        iFile.ignore();
        iFile.getline(content, 500);
        Element* tempOwner = searchUser(owner_id);
        if (tempOwner == nullptr) {
            tempOwner = searchPage(owner_id);
        }
        socialComments[i] = new Comment(id, content, tempOwner, searchPost(post_id));
        Post* tempPostOwner = searchPost(post_id);
        tempPostOwner->AddComment(socialComments[i]);
        socialComments[i]->setParentPost(tempPostOwner);
    }
    // cout << socialPosts[2]->getComments()[0]->getConent()->getString() << endl;
}

void SocialNetwork::InputUser(const char* usersFileName) {
    ifstream iFile(usersFileName);
    if (!iFile.is_open()) {
        cerr << "Error: Unable to open file " << usersFileName << endl;
        return;
    }

    iFile >> TotalUsers;
    socialUsers = new User * [TotalUsers];

    for (int i = 0; i < TotalUsers; i++) {
        char id[10];
        char f_name[30];
        char l_name[30];
        iFile >> id >> f_name >> l_name;
        socialUsers[i] = new User(id, f_name, l_name);
    }

    char tempInput[10];
    for (int i = 0; i < TotalUsers; i++) {
        while (iFile >> tempInput) {
            if (Char::strcmp(tempInput, "-1")) {
                while (iFile >> tempInput) {
                    if (Char::strcmp(tempInput, "-1")) {
                        break;
                    }
                    else {
                        Page* tempPage = searchPage(tempInput);
                        if (tempPage != nullptr) {
                            socialUsers[i]->addPage(tempPage);
                            tempPage->addFollower(socialUsers[i]);
                        }
                    }
                }
                break;
            }
            else {
                User* tempFrnd = searchUser(tempInput);
                if (tempFrnd != nullptr) {
                    socialUsers[i]->addFriend(tempFrnd);
                }
            }
        }
    }
}

void SocialNetwork::InputPages(const char* filename)
{

    ifstream iFile(filename);
    if (!iFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }
    iFile >> totalPages;

    Social_Pages = new Page * [totalPages];
    cout << endl << totalPages << endl;
    for (int i = 0; i < totalPages; i++) {
        char id[10];
        char name[100];
        iFile >> id;
        iFile.ignore();
        iFile.getline(name, 100);
        Social_Pages[i] = new Page(id, name);
    }

}

void SocialNetwork::InputPosts(const char* filename) {
    ifstream iFile(filename);
    if (!iFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    iFile >> totalPosts;

    char value[500];
    char id[10];
    char ownerID[10];
    char mem[100];
    int d, m, y, MemoryType, sections;
    Social_Posts = new Post * [totalPosts];
    for (int i = 0; i < totalPosts; i++) {
        MemoryType = -1;
        iFile >> sections;
        iFile >> id >> d >> m >> y;
        iFile.ignore();
        iFile.getline(value, 500);
        if (sections == 2) {
            iFile >> MemoryType;
            iFile.getline(mem, 100);
        }
        iFile >> ownerID;

       
        Element* tempPtr;
        tempPtr = searchUser(ownerID);
        if (tempPtr == nullptr) {
            tempPtr = searchPage(ownerID);
        }

   
        if (tempPtr != nullptr) {
            Social_Posts[i] = new Post(id, value, d, m, y, tempPtr, MemoryType, mem);
            tempPtr->addPost(Social_Posts[i]);
        }

        //cout << "Post Created \n\n\n";
        char tempInput[10];
        while (iFile >> tempInput) {
            if (!(Char::strcmp(tempInput, "-1"))) {

                Element* TEMP;
                //cout << tempInput << endl;
                TEMP = searchUser(tempInput);
                if (TEMP == nullptr) {
                    TEMP = searchPage(tempInput);
                }
                Social_Posts[i]->LikePost(TEMP);
            }
            else { break; }
        }
    }

}

void SocialNetwork::setTime(int d, int m, int y) {
    this->CurrentDate.setDay(d);
    this->CurrentDate.setMonth(m);
    this->CurrentDate.setYear(y);
}

SocialNetwork::SocialNetwork() {
   totalNoofMemories= totalComments = totalPages = totalPosts = TotalUsers = 0;
    Social_Posts = nullptr;
    Social_Pages = nullptr;
    socialComments = nullptr;
    socialUsers = nullptr;
    memories = nullptr;
    CurrentUser = nullptr;
}



void SocialNetwork::LoadApp() {
 
    this->setTime(10, 5, 2024);
    cout << "Current date: \t";
    CurrentDate.ViewDate();

    InputPages("pages.txt");
    InputUser("user.txt");
    InputPosts("post.txt");
    InputComments("comments.txt");
    //cout << endl << socialPages[4]->getFollowersCount();
}

void SocialNetwork::runApp() {
    
  
    const char* lineBreak = "-----------------------------------------------------------------------";
    cout << "Command : Set Program Time 15 11 2017" << endl;
    this->setTime(15, 11, 2017);
    cout << "System Date: ";
    this->CurrentDate.ViewDate();
    //cout << endl << "Enter user:" << endl;
    cout << endl << "Command: Set current user u1";
    this->setCurrentUser("u1");
    cout << endl << this->CurrentUser->getName() << " set as current User" << endl;
    cout << endl << "Command: View friend list" << endl;
    this->CurrentUser->viewFriendList();
    cout << lineBreak;
    cout << endl << "Command: View Liked pages" << endl;
    cout << lineBreak;
    this->CurrentUser->viewLikedPages();
    cout << lineBreak;
    PrintHome();
    cout << lineBreak;
    viewTimeline();
    cout << lineBreak;
    viewLikedList("post5");
    cout << lineBreak;
    likePost("post5");
    viewLikedList("post5");
    cout << lineBreak;
    postComment("post4", "please God help Pakistan to win world cup");
    viewPost("post4");
    cout << lineBreak;
    postComment("post8", "Watching ucl Real Madrid vs Bayern Munich semi final leg 2");
    viewPost("post8");
    cout << lineBreak;
    cout << endl << "Command: view Memory(post 8)" << endl;
    CurrentUser->ViewMemory();
    cout << lineBreak<<endl;
    cout << "Command:\t ShareMemory(post10,\"never thought I will be specialist in this field ...\")" << endl;
    ShareMemory("post 10", "never thought I will be specialist in this field");
    cout << lineBreak << endl;
    createUser("u21", "Saboor Islam");
    setCurrentUser("u21");
    CurrentUser->addFriend(searchUser("u1"));
    CurrentUser->addFriend(searchUser("u8"));
    CurrentUser->addFriend(searchUser("u20"));
    CurrentUser->addPage(searchPage("p2"));
    CurrentUser->addPage(searchPage("p9"));
    CurrentUser->addPage(searchPage("p900"));
    CurrentUser->viewFriendList();
    cout << lineBreak;
    CurrentUser->viewLikedPages();
    cout << lineBreak;
    createPage("p13", "Halla Madrid!");
    cout << endl << "Command: ViewPage(p1)" << endl;
    viewPage("p1");
    cout << endl << lineBreak;

}

SocialNetwork::~SocialNetwork() 
{
 
    for (int i = 0; i < TotalUsers; i++) {
        if (socialUsers[i] != nullptr) {
            delete socialUsers[i];
        }
    }
    delete[] socialUsers;

    

    for (int i = 0; i < totalPages; i++) {
        if (Social_Pages[i] != nullptr) {
            delete Social_Pages[i];
        }
    }

    

    for (int i = 0; i < totalComments; i++) {
        if (socialComments[i]) {
            delete socialComments[i];
        }
    }
    delete[] socialComments;


    for (int i = 0; i < totalPosts; i++) {
        if (Social_Posts[i]) {
           delete Social_Posts[i];
        }
    }
    delete[] Social_Posts;

    for (int i = 0; i < totalNoofMemories; i++) {
        if (memories[i]) {
            delete memories[i];
        }
    }
    delete[] memories;
    totalComments = totalPages = totalPosts = TotalUsers = 0;
   memories = nullptr;
    Social_Posts = nullptr;
    Social_Pages = nullptr;
    socialComments = nullptr;
    socialUsers = nullptr;

    CurrentUser = nullptr;
}


int main() {


    SocialNetwork Instagram;
    Instagram.LoadApp();
    Instagram.runApp();
    

    return 0;
}
    
