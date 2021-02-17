#define BOOST_TEST_MODULE mytests

#include "../fromsomeapi_info_provider/controller.hpp"
#include "../fromsomeapi_info_provider/iview.h"
#include "../fromsomeapi_info_provider/curl_sender.hpp"
#include "../fromsomeapi_info_provider/json_parser.hpp"

#include <boost/test/included/unit_test.hpp>

#include <algorithm>

//#define _TINPUT

std::string const apiLink = "https://api.unsplash.com/";

std::string testUsername = "testUsername";
std::string testPassword = "testPassword";
json outputJSON;

class TestView final : public IView
{
public:
	void setAssetNumber(std::size_t const index) noexcept override
	{
		m_index = index;
	}

	void get(Model const& model) const noexcept override
	{
		outputJSON = parseJSON(model.get(), m_index);
	}
private:
	std::size_t m_index = 0;
};

BOOST_AUTO_TEST_CASE(ModelViewTest)
{
	outputJSON = json{};
	
	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());
	
	Model model( R"([{"id":"some_id1"}])" );
	
	viewPtr->get(model);

	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id1");
}

BOOST_AUTO_TEST_CASE(MVCTest)
{
	outputJSON = json{};

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	Model model(R"([{"id":"some_id2"}])");

	Controller controller(model, viewPtr);

	controller.getResult();

	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id2");
}

BOOST_AUTO_TEST_CASE(MainTest)
{
#ifdef _TINPUT
	// Almost defMain();
	
	std::cout << "Test: Enter username: ";
	std::cin >> testUsername;
	std::cout << "Test: Enter password: ";
	std::cin >> testPassword;
	std::size_t const index = 0;

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	Model model = getModel(testUsername, testPassword, apiLink);

	Controller controller(model, viewPtr);

	controller.setAssetNumber(index);

	controller.getResult();

	BOOST_CHECK_EQUAL(outputJSON["filename"], "EwgqRnJT9gE");
	BOOST_CHECK_EQUAL(outputJSON["filesize"], 11376774);
	BOOST_CHECK_EQUAL(outputJSON["modifiedTime"], "2021-02-17T16:11:19-05:00");
	BOOST_CHECK_EQUAL(outputJSON["uploadTime"], "2021-02-17T16:11:18-05:00");
#else
	std::cout <<
		"The test \"MainTest\" requires user input. If you able to enter from keyboard - define _TINPUT"
	<< std::endl;
#endif // _TINPUT //
}