// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	tableSize = 1500;
	table = new XUser*[tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr; 
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < tableSize; i++) {
        delete table[i];
    }
    delete[] table;
}

XUser* HashTable::createUser(string username, string userBio)
{
	XUser* user = new XUser;
	user->username = username;
	user->userBio = userBio;
	user->bst = new BST;
	return user;
}

unsigned int HashTable::hashFunction(string username)
{
	unsigned int key = 0;
	for(std::string::iterator c = username.begin(); c != username.end(); ++c)
	{
		key += static_cast<unsigned int>(*c);
	}
	key = key % tableSize;
	return key;
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{

	if(searchUser(username))
	{
		cout <<"username taken" << endl;;
		return NULL;
	}

	int key = hashFunction(username);
	XUser* user = createUser(username, userBio);
	if(table[key])
	{
		numCollision++;
	}
	user->next = table[key];
	table[key] = user;
	return user;
}

XUser* HashTable::searchUser(string username)
{
	int key = hashFunction(username);
	XUser* user = table[key];
	if(! user || user->username.compare("") == 0){
		return nullptr;
	}
	while(user)
	{
		if((user->username).compare(username) == 0)
		{
			return user;
		}
		user = user->next;
	}

	return nullptr;
	
}

void HashTable::printUsers()
{
	for(int i = 0; i < tableSize; i++)
	{
		XUser* user = table[i];
		if(user){
		cout << i << "|";
		while(user)
		{
			cout << user->username << "-->";
			user = user->next;
		}
		cout << "NULL" << endl;}
	}
}

void HashTable::printAllPostByUser(string username) 
{
	XUser* user = searchUser(username);
	if(! user){cout << "User does not exist, try again..." << endl; return;}
	cout << user->username << ":" << endl;
	cout <<"| postCount: " << user->postCount << endl;
	cout << "| userBio: " << user->userBio << endl;
	cout <<"| Posts: " << endl;
	user->bst->displayPosts();
}

void HashTable::printMostLikedPost() 
{
	XPost* post;
	XUser* mostU;
	for(int i = 0; i < tableSize; i++)
	{
		for(XUser* user = table[i]; user; user = user->next)
		{
			XPost* temp = user->bst->mostPopular();
			if(temp->likes > post->likes)
			{
				post = temp;
				mostU = user;
			}
		}
	}

	cout << "Most liked post by: " << mostU->username << endl;;
	cout <<"| Postcount: " << mostU->postCount << endl;
	cout <<"__| Post: " << post->likes << endl;
	cout << post->postedTime << ":" <<endl;
	cout <<"__| Likes: " << post->likes << endl;
	cout << "__| " << post->xContents << endl;

}

int HashTable::longestChain() 
{
	int count = 0;

	for(int i = 0; i < tableSize; i++)
	{
		int temp = 0;
		for(XUser* user = table[i]; user != NULL; user = user->next)
		{	
			temp++;
		}
		if(temp > count)
		{
			count = temp;
		}
	}

	return count;
}
    
