#define BOOST_TEST_MODULE mytests

#include "../fromsomeapi_info_provider/fromsomeapi_info_provider.hpp"

#include <boost/test/included/unit_test.hpp>

#include <algorithm>

//#define _TINPUT

std::string const apiLink = "https://api.unsplash.com/";

std::string testUsername = "testUsername";
std::string testPassword = "testPassword";
std::string output;

std::string& getOutputString() { return output; }

class TestView final : public IView
{
public:

	void set(std::string& username, std::string& password) const override
	{
		username = testUsername;

		password = testPassword;
	}

	void get(Model const& model) const noexcept override
	{
		 getOutputString() = model.get();
	}
};

BOOST_AUTO_TEST_CASE(ModelViewTest)
{
	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());
	
	Model model( "[{\"id\":\"some_id\"}]" );
	
	std::string username;
	std::string password;

	viewPtr->set(username, password);

	BOOST_REQUIRE_EQUAL(username, "testUsername");
	BOOST_REQUIRE_EQUAL(password, "testPassword");

	viewPtr->get(model);

	BOOST_CHECK_EQUAL(output, "[{\"id\":\"some_id\"}]");
}

BOOST_AUTO_TEST_CASE(MVCTest)
{
	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	Model model;

	// Almost 'model = getModel();'
	{
		std::string username;
		std::string password;
		viewPtr->set(username, password);

		BOOST_REQUIRE_EQUAL(username, "testUsername");
		BOOST_REQUIRE_EQUAL(password, "testPassword");

		std::string const link = apiLink + "users/" + username + "/photos";
		std::string const auth = "?client_id=" + password;

		model.set(link + auth);
	}

	Controller controller(model, viewPtr);

	controller.getResult();

	BOOST_CHECK_EQUAL(
		output,
		"https://api.unsplash.com/users/testUsername/photos?client_id=testPassword"
	);
}

BOOST_AUTO_TEST_CASE(MainTest)
{
	// Almost defMain();

#ifdef _TINPUT
	std::cout << "Test: Enter username ";
	std::cin >> testUsername;
	std::cout << "Test: Enter password ";
	std::cin >> testPassword;

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	Model model = getModel(viewPtr, apiLink);

	Controller controller(model, viewPtr);

	controller.getResult();

	std::string newOutput = output.substr(2, 146);
	BOOST_CHECK_EQUAL(
		newOutput,
		"\"id\":\"ZLkHfhf1YrE\",\"created_at\":\"2021-02-16T11:13:48-05:00\",\"updated_at\":\"2021-02-16T11:13:49-05:00\",\"promoted_at\":null,\"width\":2784,\"height\":4176"
	);
#else
	std::cout <<
		"The test \"MainTest\" requires user input. If you able to enter from keyboard - define _TINPUT"
	<< std::endl;
#endif // _TINPUT //
}