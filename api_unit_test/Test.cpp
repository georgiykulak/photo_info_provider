#define BOOST_TEST_MODULE mytests

#include "../fromsomeapi_info_provider/controller.hpp"
#include "../fromsomeapi_info_provider/model.hpp"
#include "../fromsomeapi_info_provider/iview.h"
#include "../fromsomeapi_info_provider/curl_sender.hpp"

#include <boost/test/included/unit_test.hpp>

//#define _TINPUT

std::string const apiLink = "https://api.unsplash.com/";
json outputJSON;

class TestView final : public IView
{
public:
	void get(std::unique_ptr< IModel > const& modelPtr) const override
	{
		outputJSON["filename"] = modelPtr->getFilename();
		outputJSON["filesize"] = modelPtr->getFilesize();
		outputJSON["modifiedTime"] = modelPtr->getModifiedTime();
		outputJSON["uploadTime"] = modelPtr->getUploadTime();
	}
};

BOOST_AUTO_TEST_CASE(ModelViewTest)
{
	outputJSON = json{};

	std::unique_ptr< IModel > modelPtr(std::make_unique< Model >());

	modelPtr->set(R"([{"id":"some_id1"}])");

	modelPtr->parse();
	
	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	viewPtr->get(modelPtr);

	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id1");
}

BOOST_AUTO_TEST_CASE(MVCTest)
{
	outputJSON = json{};

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	std::unique_ptr< IModel > modelPtr(std::make_unique< Model >());

	modelPtr->set(R"([{"id":"some_id2"}])");

	Controller controller(modelPtr, viewPtr);

	controller.chooseAsset(0);

	controller.getResult();

	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id2");
}

BOOST_AUTO_TEST_CASE(MainTest)
{
#ifdef _TINPUT
	// Almost defMain();
	std::string testUsername;
	std::cout << "Test: Enter username: ";
	std::cin >> testUsername;
	std::string testPassword;
	std::cout << "Test: Enter password: ";
	std::cin >> testPassword;
	std::size_t const index = 0;

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	std::unique_ptr< IModel > modelPtr(std::make_unique< Model >());

	getModel(modelPtr, testUsername, testPassword, apiLink);

	Controller controller(modelPtr, viewPtr);

	controller.chooseAsset(index);

	controller.getResult();

	BOOST_CHECK_EQUAL(outputJSON["filename"], "EwgqRnJT9gE");
	BOOST_CHECK_EQUAL(outputJSON["filesize"], 11376774);
	BOOST_CHECK_EQUAL(outputJSON["modifiedTime"], "2021-02-17T16:26:40-05:00");
	BOOST_CHECK_EQUAL(outputJSON["uploadTime"], "2021-02-17T16:11:18-05:00");
#else
	std::cout <<
		"The test \"MainTest\" requires user input. If you able to enter from keyboard - define _TINPUT"
	<< std::endl;
#endif // _TINPUT //
}