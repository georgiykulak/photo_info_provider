#define BOOST_TEST_MODULE mytests

#include "../fromsomeapi_info_provider/fromsomeapi_info_provider.hpp"

#include <boost/test/included/unit_test.hpp>

//#define _TINPUT

std::string testUsername = "testUsername";
std::string testPassword = "testPassword";
std::string* output;

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
		 *output = model.get();
	}
};

BOOST_AUTO_TEST_CASE(ModelViewTest)
{
	Model model( "[{id:\"some_id\"}]" );

	std::string username;
	std::string password;
	output = new std::string();

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	viewPtr->set(username, password);

	BOOST_CHECK_EQUAL(username, "testUsername");
	BOOST_CHECK_EQUAL(password, "testPassword");

	viewPtr->get(model);

	BOOST_CHECK_EQUAL(*output, "[{id:\"some_id\"}]");

	delete output;
}

BOOST_AUTO_TEST_CASE(MainTest)
{
	// Almost defMain();

#ifdef _TINPUT
	output = new std::string();

	std::string const apiLink = "https://api.unsplash.com/";

	std::cout << "Test: Enter username" << std::endl;
	std::cin >> testUsername;
	std::cout << "Test: Enter password" << std::endl;
	std::cin >> testPassword;

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	Model model = getModel(viewPtr, apiLink);

	Controller controller(model, viewPtr);

	controller.getResult();

	std::cout << *output << std::endl;

	delete output;
#else
	std::cout <<
		"The test requires user input. If you able to enter from keyboard - define _TINPUT"
	<< std::endl;
#endif // _TINPUT //
}