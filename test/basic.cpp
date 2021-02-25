#define BOOST_TEST_MODULE mytests

#include <controller.hpp>
#include <model_unsplash.hpp>
#include <iview.hpp>
#include <curl_sender.hpp>

#include <boost/test/included/unit_test.hpp>

//#define _TINPUT

std::string const apiLink = "https://api.unsplash.com/";
json outputJSON;

class TestView final : public IView
{
public:
	void readUsername ( std::string & testUsername ) const override
	{
		std::cout << "Test: Enter username: ";
		std::cin >> testUsername;
	}

	void readPassword ( std::string & testPassword ) const override
	{
		std::cout << "Test: Enter password: ";
		std::cin >> testPassword;
	}
	
	void readAssetNumber ( std::size_t & index ) const override
	{
		index = 0;
	}

	void get(std::unique_ptr< IModel > const& modelPtr) const override
	{
		auto const& resPair = modelPtr->getResponse();
		outputJSON["response"][std::to_string(resPair.first)] = resPair.second;

		if (resPair.first == modelPtr->getSuccessCode())
		{
			outputJSON["filename"] = modelPtr->getFilename();
			outputJSON["filesize"] = modelPtr->getFilesize();
			outputJSON["modifiedTime"] = modelPtr->getModifiedTime();
			outputJSON["uploadTime"] = modelPtr->getUploadTime();
			outputJSON["description"] = modelPtr->getDescription();
			outputJSON["linkToPhoto"] = modelPtr->getLinkToPhoto();
		}
	}
};

BOOST_AUTO_TEST_CASE(ModelViewTest)
{
	outputJSON = json{};

	std::unique_ptr< IModel > modelPtr(std::make_unique< ModelUnsplash >());

	modelPtr->set(R"([{"id":"some_id1"}])");

	modelPtr->parse();
	
	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	viewPtr->get(modelPtr);

	BOOST_REQUIRE(outputJSON.contains("response"));
	BOOST_REQUIRE(outputJSON["response"].contains("200"));
	BOOST_REQUIRE_EQUAL(outputJSON["response"]["200"], "The operation was successful");
	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id1");
}

BOOST_AUTO_TEST_CASE(MVCTest)
{
	outputJSON = json{};

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	std::unique_ptr< IModel > modelPtr(std::make_unique< ModelUnsplash >());

	modelPtr->set(R"([{"id":"some_id2"}])");

	Controller controller(std::move( modelPtr ), std::move( viewPtr ));

	controller.getResult();

	BOOST_REQUIRE(outputJSON.contains("response"));
	BOOST_REQUIRE(outputJSON["response"].contains("200"));
	BOOST_REQUIRE_EQUAL(outputJSON["response"]["200"], "The operation was successful");
	BOOST_CHECK_EQUAL(outputJSON["filename"], "some_id2");
}

BOOST_AUTO_TEST_CASE(MainTest)
{
#ifdef _TINPUT
	// Almost defMain();
	outputJSON = json{};

	std::unique_ptr< IView > viewPtr(std::make_unique< TestView >());

	std::unique_ptr< IModel > modelPtr(std::make_unique< ModelUnsplash >());

	Controller controller(std::move( modelPtr ), std::move( viewPtr ));

	controller.fetchContent();

	controller.getResult();

	BOOST_REQUIRE(outputJSON.contains("response"));
	BOOST_REQUIRE(outputJSON["response"].contains("200"));
	BOOST_REQUIRE_EQUAL(outputJSON["response"]["200"], "The operation was successful");
	BOOST_CHECK_EQUAL(outputJSON["filename"], "MpbRU6LY31k");
	BOOST_CHECK_EQUAL(outputJSON["filesize"], 11376774);
	BOOST_CHECK(!outputJSON["modifiedTime"].empty());
	BOOST_CHECK(!outputJSON["uploadTime"].empty());
	BOOST_CHECK_EQUAL(outputJSON["description"], "Just a beautiful woman");
	BOOST_CHECK_EQUAL(
		outputJSON["linkToPhoto"],
		"https://images.unsplash.com/photo-1613976368854-0e51cb8353cf?ixid=MXwyMDczMDh8MHwxfGFsbHwxfHx8fHx8Mnw&ixlib=rb-1.2.1"
	);
#else
	std::cout <<
		"The test \"MainTest\" requires user input. If you able to enter from keyboard - define _TINPUT"
	<< std::endl;
#endif // _TINPUT //
}