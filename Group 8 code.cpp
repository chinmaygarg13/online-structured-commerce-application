///Chorbazar online structured portal for customer and vendor


#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

///Conio.h wont work in linux/ubuntu distribution
#include<conio.h>
#include<vector>
#include<time.h>
#include<map>
#define def_tax 5.0
using namespace std;

///Class declarations
class Customer;
class Vendor;

///Declaration of User class. User Class is the backbone of the code. It defines the way a person will be able to access the data.
///It is the base class for 2 classes, namely Customer and Vendor
class User
{
	public:
		
///Type field to store which specific type of user. Virtual also used below		
	enum user_type {V,C};
	user_type type;
	string name;
	string user_id;
	string password;
	string email;
	string address;
	int age;
	long long contact;	
	string security_qn;
	string security_ans;
	
	public:	
	friend int vector_index(string);//returns index of the User in vector<User *>
	friend void register_user();//Constructs a User by interactive input from IO
	friend User* login_user(); //Verifies entered credentials and prevents brute force attacks by a mechanism
    virtual void profile();///DECLARED VIRTUAL SO THAT ALL SUBCLASSES' PROFILE CAN BE CALLED AUTOMATICALLY
	user_type get_type()const;
    string get_name()const;
    
    ///seeProfile outputs the User parameters
    void seeProfile(){
//		char s1[100],s2[100],s3[100],s4[100];
//		int i;
//		for(i=0;i<user_id.length();i++){
//			s1[i]=user_id[i];
//		}	s1[i]='\0';
//		for(i=0;i<email.length();i++){
//			s2[i]=email[i];
//		}	s2[i]='\0';
//		for(i=0;address.length();i++){
//			s3[i]=address[i];
//		}	s3[i]='\0';
////		for(int i=0;i < contact.length();i++){1
////			s[3][i]=contact[i];
////		}
//		for(i=0;i<security_qn.length();i++){
//			s4[i]=security_qn[i];
//		}	s4[i]='\0';
//		printf("%-25s%-100s%-10s\n", "Name:", s1," ");
//		printf("%-25s%-100s%-10s\n", "Email Id:", s2," ");
//		printf("%-25s%-100s%-10s\n", "Address:", s3," ");
//		printf("%-25s%-100d%-10s\n", "Age:", age," ");
//		printf("%-25s%-100ll%-10s\n", "Contact Number:",contact," ");
//		printf("%-25s%-100s%-10s\n", "Security Question:",s4," ");		
	cout<<"Name:           "<<name<<endl;
	cout<<"Email-ID        "<<email<<endl;
	cout<<"Address:        "<<address<<endl;
	cout<<"Age:            "<<age<<endl;
	cout<<"Contact Number: "<<contact<<endl;
	
	}
    
};
vector <User> userobj;

///Data storage of users' data irrespective of type (Customer or Vendor)
vector<User*> users;

bool login; //Variable to determine current status:login/logout

///profile version of the virtual profile of the baseclass User
void User::profile()
{
	cout<<"User profile is as follows:\n";
}

User::user_type User::get_type()const
{
	return type;
}

string User::get_name()const
{
	return name;
}

class Captcha //Completely Automated Public Turing test to tell Computers and Humans Apart 
{
	private:
	string captcha;
	string input;
	public:
	Captcha()
	{
   		captcha="";
		input="";
		captcha_verification();
	}
	void generate_captcha();
	void accept_input();	
	bool match_captcha() const;
	void captcha_verification();
};

void Captcha::generate_captcha()
{
	string new_captcha="";
	///srand generates random numbers and seeds them according to the timestamps
	srand(time(NULL));
	while(new_captcha.length()<8)
	{
		int i=rand();
		if((i>=65&&i<=90)||(i>=97&&i<=122))
	   	{
	   		new_captcha+=(char)(i);
	    }
	}
	captcha=new_captcha;
	cout<<"CAPTCHA : "<<captcha<<endl;
}

void Captcha::accept_input()
{
	cout<<"Please enter the captcha shown above to complete the verification: \n";
	cin>>input;
}

bool Captcha::match_captcha() const
{ 
   	return (strcmp(captcha.c_str(),input.c_str())==0)?1:0 ;
}

void Captcha::captcha_verification()
{
	system("CLS");
	cout<<"Directing for captcha verification in \n";
	for(int i=3;i>0;i--)
	{
		cout<<i<<"\n";
		sleep(1);
	}
	cout<<"0"<<endl;
	cout<<endl;
	while(1)
	{
		generate_captcha();
		accept_input();
	    if(match_captcha())
	    {
		   	cout<<"Captcha verification success.\n";
	    	system("pause");
	    	break;
		}
		else
		{
			/* Captcha and input dont match */
			cout<<"Input does not match with captcha.\n";
			cout<<"Try again in 2 seconds !\n\n";
			sleep(2);
			srand(time(NULL));
			continue;
		}
	}		
}

///END CAPTCHA FUNCTIONS


///This function returns the index of the object pointer in users
int vector_index(string s)
{
	int flag=-1; // user_id not found
	for(int i=0;i<users.size();i++)
	{
		if(!strcmp((users[i]->user_id).c_str(),s.c_str()))
		{
			flag=i;
		}
	}
	return flag;
}

string get_password(string s) 
/*
	s is the user id which is passed to print the user_id again to the screen in 
   	the event of a backspace press
*/   
{
	system("CLS");
//	cout<<"";
	cout<<"User ID : "<<s<<endl;
	cout<<"Password : ";
	int i=0; //keeps track of length
	string pwd;
	char ch;
	do
	{	   
	   	ch=getch();  //accepts a character from the user without displaying to the screen 
		if(ch==13)   //carriage return a.k.a. enter key
		   break;
		else if (ch==8)  //8-backspace 
		  {
		  	i-=1;
		  	pwd=pwd.substr(0,i);
		  	system ("CLS");
			cout<<"User ID : "<<s<<endl;
			cout<<"Password : ";
		  	for(int j=0;j<i;j++)
		  	  cout<<"*";
		  }
		else
		{  
			i++;         //maintains track of size of password
			pwd+=ch;
	   		cout<<"*";
	    }
	} while (1);
    cout<<endl;
	return pwd;
}

/* To convert string to long long */
long long string_to_long_long(const string& s)
{
	long long n=0;
	char ch;
	for(int i=0;i<s.length();i++)
	{
		ch=s.at(i);
		if(ch<48||ch>57)
		{
			n=-1;
			break;
		}
		else
		{
			n=n*10+(ch-48);
		}
	}
	return n;
}

/* To check if contact number is valid or not */
bool valid_contact_number(long long n)
{
	int l=0;
	long long max=10000000000; // for 10 digit contact number
    long long copy=n;
    while(copy!=0)
    {
    	l++;
    	copy=copy/10;
	}
	if(l==10&&n!=-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///Product class is the 2nd pillar of the code. It defines a way in which a product data is to be handled and stored

class Product
{
public:
//    friend class Deliver::Vendor;
    int qty_left;
    string product_name;
    string category;
    double price;
    double tax_rate;
    /*User_operations::*/User vendor;
    double disc;

    //check what is the id of the last product formed. Add 1 to that and allocate it to this product
    ///Constructor of Product class defined to initialise it with basic values
    Product(string name="", string cat="miscellaneous", double pr=0.0, double trate=def_tax, int qty=0)
    {
        product_name=name;
        category=cat;
        price=pr;
        tax_rate=trate;
        qty_left=qty;
    }
    double get_price()
    {
        return price;
    }
    string get_product_name()const {
        return product_name;
    }
    
    ///This function is used whenever a brief info is to be displayed about the product
    void print_product_details()
    {
        cout<<"Product Name:    "<<product_name<<endl;
        cout<<"Category name:   "<<category<<endl;
		cout<<"Price:           "<<price<<endl;
		cout<<endl;
    }
    void update_qty(int decrease_by)
    {
        if(qty_left>=decrease_by)
        {
            qty_left-=decrease_by;
        }
        else
        {
            cout<<"THE QUANTITY TO BE DECREASED IS GREATER THAN TOTAL CURRENT QUANTITY. PLEASE TRY AGAIN "<<endl;
        }
    }
    /*overload << operator */
};


///MEANS OF HANDLING stocklist. Stocklist serves like an interface between vendor and customer class. map<string, vector<Product> > means key is category and value is a vector of all Product objects under the category
map<string,vector<Product> > stocklist;
map<string,vector<Product> > orders;


///Cart class instance is declared inside the Customer class. It represents an organised set of Products, the customer is willing to buy
class Cart
{
    public:
    map<Product*,int > chosen;///How much of the product is to be added is the value and a reference to the Product object stored inside stocklist is the key
    void add_to_cart(Product *p,int qty)
    {
     //   chosen.push_back(make_pair(p,qty)); GIVES AN ERROR BECAUSE PUSH_BACK DOESNT EXIST FOR MAP
     chosen[p]=qty;
    }
    //void notify_vendor();
    float get_subtotal(int i)/// Simple code to multiply the qty with the price and return the same
	 {
    	map<Product*,int>::iterator iter=chosen.begin();
    	for(int j=0;j<i;j++)
    	{
    		iter++;
		}
        return ((*iter).second)*(((*iter).first)->get_price());
    }
    void incart();///calls all operations on cart eg. Deletion, go_back to shop,modify qty, checkout etc
    void checkout() {
        cout<<"connecting...";
    }
    // void in_cart(int);
    void print_cart();///PRINTS ITEMS IN CART AND THEN CALLS INCART()
    void change_qty();
    void delete_product();
};

void Cart::change_qty()
{
    bool flag=false;
    while(!flag)
    {
        string naam;
        cout<<"Enter the name of the product you wish to change qty for "<<endl;
        cin>>naam;
        int nq;
        cout<<"Enter the new quantity "<<endl;
        cin>>nq;
        map <Product *, int>::iterator it=chosen.begin();
        for(; it!=chosen.end(); it++)
        {
            if(it->first->product_name==naam)
            {
                it->second=nq;
                flag=true;
                return;
				break;
            }
        }
        if(!flag)
        {
            cout<<"Please enter the name correctly. TRY AGAIN "<<endl;
        }
    }
}


///Deletes product from Cart
void Cart::delete_product()
{
    bool flag=false;
    while(!flag)
    {
        cout<<"If you didnt like it you can always delete it by entering the name of the product...'"<<endl;
        string n;
        cin>>n;

        map <Product *, int>::iterator it=chosen.begin();
        for(; it!=chosen.end(); it++)
        {
            if(it->first->product_name==n)
            {
            	///Note that erase doesnt call the destructor in case of pointer types but calls it otherwise
                chosen.erase(it);
                flag=true;
                break;
            }
        }
        if(!flag)
        {
            cout<<"Please enter the name correctly. TRY AGAIN  "<<endl;
        }

    }
}


///DRIVER FUNCTION FOR CART CLASS. Calls all other functions in cart
void Cart::incart()
{
    int m;
    
    while(1)
    {	cout<<"Select the function you wish to proceed with:\n1. Continue shopping.\n2. Proceed to checkout.\n3. Change quantity of a product.\n4. Delete a product.\n";
    	cin>>m;
        switch(m)
        {
        case 1:
            return;///continue shopping
        case 2:
            checkout();//connects for payment portal
            return;
            break;
        case 3:
            change_qty();
//            incart();
			break;
        case 4:
            delete_product();
            break;
        }
    }
}

///prints all elements and then calls incart()
void Cart :: print_cart() {
    float sum = 0, curr=0;
    for(int i = 0; i < chosen.size(); i++) {
        curr = get_subtotal(i);
        sum += curr;
        cout<<i+1<<".  "<<endl;
        
        ///iterator or a pointer to a key, value pair stored in a map
        map<Product*,int>::iterator iter=chosen.begin();
    	for(int j=0;j<i;j++)
    	{
    		iter++;
		}
        (iter->first)->print_product_details();
        cout<<"  Quantity: "<<iter->second<<endl<<"  Subtotal: "<<curr<<"/-\n";
    }
    cout<<"\nYour total amount is: Rs. "<<sum<<"/-\n\n";
    incart();
}




///Customer Class is the 3rd Pillar of the code. It inherits from the User class and contains an instance of the Cart class
class Customer:public User
{
    Cart my_cart;
public:
	
    void profile();///VIRTUAL PROFILE VERSION OF THE CUSTOMER CLASS
    void add_cat_prod();///ADD PRODUCTS TO THE CART
    void show_stock_list();///SHOW WHOLE STOCKLIST AND THEN CALLS add_cat_prod()
    Customer(User obj):User(obj){///Constructor used in register
    	
	}
};

//Prints the stocklist by simply traversing it 
void Customer::show_stock_list() {
    map <string,vector<Product> >::iterator it=stocklist.begin();
    for(; it!=stocklist.end(); it++)
    {
        for(int i=0; i<it->second.size(); i++) {
            it->second[i].print_product_details();
        }
        
    }
    add_cat_prod();
}
//asks for category and the name of the product for a faster searching in stocklist
void Customer::add_cat_prod()
{
    bool flag=false;
    while(!flag)
    {
        string cat,name123;
        cout<<"PLEASE ENTER THE CATEGORY AND NAME OF PRODUCT YOU WISH TO BUY "<<endl;
        cin>>cat>>name123;
        cout<<"ALSO ENTER THE QUANTITY TO BE BOUGHT "<<endl;
        int q;
        cin>>q;
        for(int i=0; i<stocklist[cat].size(); i++)
        {
            if(name123==stocklist[cat][i].get_product_name())
            {
                flag=true;
                my_cart.add_to_cart(&stocklist[cat][i],q);
                break;
            }
        }
        if(!flag)
        {
            cout<<"Please enter the name correctly. TRY AGAIN "<<endl;
        }
    }
}

void Customer::profile() //main of customer
{	while(1){
		cout<<"Hi "<<name<<"!"<<endl;
    	cout<<"What you want to do today"<<endl;
    	cout<<"1. Press 1 to go to cart"<<endl;
    	cout<<"2. Press 2 to search for items"<<endl;
//    cout<<"3. Press 3 to search category wise"<<endl;
    	cout<<"3. Press 3 to see your profile"<<endl;
    	cout<<"4. Logout"<<endl;
    	int choice;
    	cin>>choice;
    	switch(choice)
    	{
    	case 1:
    	{
        	my_cart.print_cart();//complete
        	break;
    	}	
    	case 2:
    	{   show_stock_list();
        	//Add to cart wali functionality likh dena bhai
        	break;
    	}
    	/*case 3:
        {    print_all_categories();
            filter_stock_list(category);
            break;
        }*/
    	case 3:
    	{
        	seeProfile();//Basically you need to show the user details such as name contact number
        	break;
    	}
    	case 4:
    	{  	//logs user out and returns to main
        	return;
    	}
    	
    	///Additional functions which can be completed further on
//        case 6:
//            {   modify_product(n);
//                break;
//            }
	    default:
	    {
	        cout<<"Error while entering input try again"<<endl;
	    }
    	}	
	}
}
vector<Customer>custobj;



///Similar to the class Customer, Vendor inherits User class and defines the way of handling Vendors exclusively and lets them alter stocklist
class Vendor:public/*User_operations::*/User//inherits user class
{
   // vector<string> categories;//categories he is involved in
    vector<Product *> products;//products he sells
    public:
    	
    	//Constructor(Not required hence commented out)
//    Vendor(string nm, vector<Product> prod)
//    {
//        //name=nm; call user class constructor
//        products=prod;
//    }

    void add_product();//adds product to stocklist and also list of products he sells
    void show_pending_orders();//shows pending orders
	void out_of_stock();//displays out of stock items from his part
	void modify_product();	//modify a particular product's details in stocklist
	void view_stocklist(); //prints his product_list
	void delete_product(); // deletes the product from stocklist as well as from product lists 
	void profile(); //VIRTUAL PROFILE VERSION OF VENDOR CLASS
	Vendor(User obj):User(obj){}//VENDOR CONSTRUCTOR (used at the time of register User)
};
vector<Product>prod;
vector<Vendor>vendobj;
void Vendor::add_product()
{
    string name=""; 
	string cat="miscellaneous"; 
	double pr=0.0; 
	double trate=def_tax; 
	int qty=0;
    cout<<"Enter the product name:"<<endl;
	cin>>name;
	cout<<"Enter the category of the object:"<<endl;
	cin>>cat;
	cout<<"Enter the price:"<<endl;
	cin>>pr;
	cout<<"Enter the tax rate:"<<endl;
	cin>>trate;
	cout<<"Enter the quantity in stock "<<endl;
    cin>>qty;
    Product* obj=new Product(name,cat,pr,trate,qty);
    stocklist[cat].push_back(*obj);
//    pro.push_back(*obj);
//    stocklist[cat]=pro;
	
    products.push_back(obj);
    cout<<"Product successfully added "<<endl;
}

void Vendor::show_pending_orders()
{
    for(int i=0;i<orders[name].size();i++)
    {
        (orders[name])[i].print_product_details();
    }
}

void Vendor::out_of_stock()
{
    for(int i=0;i<products.size();i++)
    {
    	if(products[i]->qty_left==0)
    	cout<<products[i]->get_product_name()<<endl;
	}   
}

void Vendor::modify_product()
{
	cout<<"Enter the product name you want to modify "<<endl;
	string name1;
	cin>>name1;
	string cat="miscellaneous"; 
	double pr=0.0; 
	double trate=def_tax; 
	int qty=0;
    cout<<"Enter new category, price, tax rate, quantity in stock "<<endl;
    cin>>cat>>pr>>trate>>qty;
    //Product *obj=NULL;
    bool flag=false;//not found
    int i=0;
    for(;i<products.size();i++)
    {
    	if(products[i]->get_product_name()==name1)
    	{
    		flag=true;
    		break;
		}
	}
	if(flag)
	{
		Product *obj=products[i];
		obj->category=cat;
		obj->price=pr;
		obj->tax_rate=trate;
		obj->qty_left=qty;
	}
	else
	{
		cout<<"Product name doesn't exist"<<endl;
	}    	
}

void Vendor::view_stocklist()
{
    //shows full stocklist of his products in all categories
    
    for(int i =0;i<products.size();i++)
    {
        products[i]->print_product_details();
    }
}

void Vendor::delete_product()
{
    string name2;
    cout<<"Enter the name of the product you would like to delete "<<endl;
    cin>>name2;
    int i;
    bool flag=false;
    for(i=0;i<products.size();i++)
    {
        if(products[i]->product_name==name2)
        {   flag=true;
            break;
        }
    }
    if(flag)
    {
        string pname=products[i]->product_name;
        string vname=(products[i]->vendor).get_name();
        string cat=products[i]->category;
        for(int j=0;j<stocklist[cat].size();j++)
        {
            if(vname==((((stocklist[cat])[j]).vendor).get_name()))
            {
                stocklist[cat].erase(stocklist[cat].begin()+j);
                break;
            }
        }
        products.erase(products.begin()+i);
        cout<<"Product successfully deleted... Redirecting to main menu"<<endl;
    }
    else
    {
        cout<<"Product not found in list... Redirecting to main menu "<<endl;
    }
}

void Vendor::profile()//main of vendor
{
    cout<<"Hi "<<name<<endl;
    
    while(1)
    {	
	    cout<<"Choose the appropriate option"<<endl;
	    cout<<"1. Add Product(s)"<<endl;
		cout<<"2. View Pending Orders \n3. View Out of Stock Products \n4. Modify Product details \n5. View stocklist \n6. Delete Product \n7. Logout"<<endl;
	    int choice;
	    cin>>choice;
    	switch(choice)
   		{
   			case 1:
    		{
        		add_product();//complete
        		break;
    		}
	        case 2:
    		{   show_pending_orders();
        		break;
    		}
	    	case 3:
    		{
        		out_of_stock();
      		    break;
    		}
    		case 4:
    		{
        		modify_product();
        		break;
    		}
    		case 5:
			{
				view_stocklist();
				break;
			}     
			case 6:
    		{   
        		delete_product();
        		break;
   			}
       		case 7:
    		{
        		return;
        		//carry out operation on logout
    		}
    		default:
    		{
        		cout<<"Error while entering input.\n Try again in 2 seconds"<<endl;
        		sleep(2);
        		continue;
    		}
        }
	}
}
/* Register and login functions of User (friend) */
void register_user()
{
	User new_user;
	while(1)
	{
		cout<<"Enter a User ID. (This User ID will be used to login each time) \n";
		string uu;
		cin>>uu;
		int existing=vector_index(uu);
		if(existing!=-1)
			{
				cout<<"User ID already in use! Try a different one!\n";
				continue;
	    	}
		else
			{
				new_user.user_id=uu;
				break;	
	    	}
    }
    
	bool match=false;
	while(!match)
	{
		cout<<"Enter a password. \n";
		string pp1=get_password(new_user.user_id);
		cout<<"Confirm password! \n";
		sleep(2);
		string pp2=get_password(new_user.user_id);

        if(!strcmp(pp1.c_str(),pp2.c_str())) 
		{
			new_user.password=pp1;
			break;
  	    }   
		else
		{
			cout<<"No match! Try again! \n";
			continue;
		}     
	}
	
	///Calls the Captcha class and checks if the Captcha entered is correct or not. IF not it will loop until correct values are entered
	Captcha();
	cout<<"Enter your name and age.\n";
	cin>>new_user.name;
	cin>>new_user.age;
	while(1)
	{
		cout<<"Are you a Customer or a Vendor (C/V) ?\n";
		///This part updates the type field of the customer or the vendor
		char ch;
		cin>>ch;
		if(ch=='c'||ch=='C')
		{
			new_user.type=User::C;
			break;
		}
		else if (ch=='v'||ch=='V')
		{
			new_user.type=User::V;
			break;
		}
		else
		{
			cout<<"Invalid input! Try again! \n";
			continue;
		}
    }
    cout<<"Update your contact and shipping details\n";
    cout<<"Enter your shipping address.\n";
    string temp1;
    long long temp2=0;
    cin.ignore();
	getline(cin,temp1);
    new_user.address=temp1;
    cout<<"Enter your email address.\n";
    getline(cin,temp1);
	new_user.email=temp1;
    cout<<"Enter your contact number.\n";
    while(1)
    {
    	getline(cin,temp1);
    	temp2=string_to_long_long(temp1);
		if(valid_contact_number(temp2))
		{
			new_user.contact=temp2;
			break;
		}
		else
		{
			cout<<"Invalid contact number!\nPlease try again.\n";
			continue;
		}
	}
    cout<<"Enter a security question! (This question will be used to reset your password in case you forget your password) \n";
    getline(cin,temp1);
    new_user.security_qn=temp1;
    cout<<"Enter an answer to the above question. \n";
    getline(cin,temp1);
    new_user.security_ans=temp1;
    
    // adding new user in the directory of users
    userobj.push_back(new_user);
//    User* pe=&new_user;
	User *pe=&userobj[userobj.size()-1];
    if(pe->type==User::C)
    {
    	Customer obj(new_user);
    	custobj.push_back(obj);
 //  	Customer* c_obj=new Customer(new_user); Doesnt work
//   	Customer* c_obj=static_cast<Customer*> (&userobj[userobj.size()-1]);  Doesnt work
    	users.push_back(&custobj[custobj.size()-1]);
	}
	if(pe->type==User::V)
    {
    	Vendor obj(new_user);
    	vendobj.push_back(obj);
    	users.push_back(&vendobj[vendobj.size()-1]);
//		Vendor* v_obj=static_cast<Vendor*> (&userobj[userobj.size()-1]); Doesnt work
//		users.push_back(v_obj); Doesnt work
	}
	cout<<"Registration successful.\n";
}


///Login function checks the credentials entered by the User and prevents brute force attacks
User* login_user()
{
	int error_count=0;
	system ("CLS");
	cout<<"User ID : ";
	string id;
	cin>>id;
	int existing=vector_index(id);
	if(existing==-1)
	{
		cout<<"No matching User ID found in our database.\n";
		cout<<"Please login again or register youself if you wish to continue\n";
		///Prompts the user to press any key to continue
	    system("PAUSE");
	    return NULL;
	}
	else
	{
    	while(error_count<3)
		{   
	    	system ("CLS");   //clear screen
	    	cout<<"User ID : "<<id<<endl;
			string correct_pwd=users[existing]->password; 
			//takes correct password from the directory	
			cout<<"Password : ";
			string pwd=get_password(id);
			cout<<endl;
			if(!strcmp(pwd.c_str(),correct_pwd.c_str()))  //string comparison
			{
				cout<<"Authentication success \n";
				return users[existing];
			}
			else
			{
				cout<<"Authentication failed ! \n";
				if(error_count<2)  //to display try again after 2 sec for the first two trials
				{
					cout<<"Please try again in 2 seconds ! \n\n";
				    sleep(2);
				}
				else
				{
					cout<<"\n";
				}	
				error_count++;	
			}
   		}
   
   cout<<"You have typed the incorrect password 3 times !\n";
   while(1)
   { 
		cout<<"Forgot password ?  Want to change password ? (Y/N) \n";
	    char choice;
   		cin>>choice;
   		if (choice=='Y'||choice=='y')
     	{
     		cout<<"Directing to change authentication details in 5 seconds\n";
     		for(int i=5;i<=0;i++)
			{
				cout<<i<<endl;
			  	sleep(1);
     	     }
			bool match=false;
			while(!match)
			{
				cout<<"Enter a password. \n";
				while(cin.get()!='\n') //waiting for next keypress
				{ }
				system("CLS");
				string pp1=get_password(id);
				cout<<endl;	
				string pp2="";
				system("CLS");
				cout<<"Confirm password! \n";
				pp2=get_password(id);
				cout<<endl;	
        		if(!strcmp(pp1.c_str(),pp2.c_str())) 
				{
					match=true;
					break;
  	    		}	   
				else
				{
					cout<<"No match! Try again! \n";
					continue;
				}     
    		}
     		break;
		}
  		else if (choice=='N'||choice=='n')
     	{
     		cout<<"Do you want to quit? Press Esc to quit else press any key to continue \n";
     		char esc;
			esc=getch();
			if(esc==27) // escape key pressed
			{
				cout<<"Thank you for using TechTiq.co.in \n";
     			exit(0);
     	    }
			else
			{
				continue;
			}
		}	 
   		else	
     	{
     		cout<<"Invalid Choice ! Please try again ! \n\n";
     		continue;
		}
    }
   }
}


///Finally the main function which calls all other functions and classes. It is the starting point of code compilation and running just after the header files are included
int main()
{
	cout<<" -----------------------------------------------Welcome to ChorBazaar.com-----------------------------------------"<<endl;
	char ch;
	bool login_status;
	try{
    while(1)
    {
    	cout<<"What would you like to do today?\n";
    	cout<<"1. Login\n";
    	cout<<"2. Register\n";
    	cout<<"3. Exit\n";
    	cin>>ch;
    	switch(ch)
    	{
    		case 49://If the person inputs 1 (ascii(1)=49)
    		{
    			User* obj=login_user();
    			if(!obj)
					continue;
    			else 
				{
					login_status=true;
//					if(obj->get_type()==User::C)
//					{
//						Customer *c_obj=static_cast<Customer*> (obj);
//						c_obj->profile();
//					}  Doesnt work
					obj->profile();
					login_status=false;
				}
    			break;
			}
    		case 50://If the person inputs 2 (ascii(2)=50)
    		{
    			register_user();
    			continue;
				break;
			}
    		case 51:
    		{
				exit(0);
			}
			default:
				cout<<"WRONG INPUT TRY AGAIN"<<endl;
		}
	}
  } 
  
  ///catches all the exceptions
  catch(...)
  {
  	cout<<"ERROR! Quitting..."<<endl;
  	exit(0);
  }
} 
