#include <iostream>
#include <curl\curl.h>

class Model
{
public:
	Model(std::string const& str)
	{
		set(str);
	}

	virtual void set(std::string const& str)
	{
		// TODO: Parse JSON
		m_data = str;
	}

	virtual std::string get() const
	{
		return m_data;
	}

private:
	// TODO: Should be JSON
	std::string  m_data;
};

class IView
{
public:
	//virtual void get(std::string const&) const noexcept = 0;
	
	virtual void get(Model const &) const noexcept = 0;
};

class CLIView final : public IView
{
public:
	//void get( std::string const & str ) const noexcept override
	//{
	//	std::cout << str << std::endl;
	//}
	
	// TODO: Upgrade soon
	void get(Model const& model) const noexcept override
	{
		std::cout << model.get() << std::endl;
	}
};

class Controller
{
public:
	Controller() = delete;

	Controller( Model const & model, std::unique_ptr< IView > viewPtr )
		: m_model{ model }
		, m_view{ std::move(viewPtr) }
	{}

	void getResult() const
	{
		m_view->get( m_model );
	}

private:
	Model const & m_model;
	std::unique_ptr< IView > m_view;
};

std::size_t WriteDataCallback(char* in, std::size_t size, std::size_t nmemb, std::string* out)
{
	if (!in)
		return 0;

	auto writeSize = size * nmemb;
	out->append(in, writeSize);

	return writeSize;
}

Model getModel()
{
	CURL* curl = curl_easy_init();

	if (!curl)
	{
		return Model("Error: Something wrong happened on curl_easy_init()");
	}

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_URL, "https://currency-converter5.p.rapidapi.com/currency/convert?format=json&from=USD&to=UAH&amount=1200&language=en");

	struct curl_slist* headers = nullptr;
	headers = curl_slist_append(headers, "x-rapidapi-key: ffe3711fc7mshb5178c5639ffd04p1bd34ajsn8b932956cd90");
	headers = curl_slist_append(headers, "x-rapidapi-host: currency-converter5.p.rapidapi.com");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallback);
	std::string response;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	curl_easy_perform(curl);

	curl_easy_cleanup(curl);

	return Model(response);
}

int main( int argc, char* argv[] )
{
	Model model = getModel();

	std::unique_ptr< IView > viewPtr( std::make_unique< CLIView >() );

	Controller controller( model, std::move( viewPtr ) );

	controller.getResult(); // get what depends on config

	return 0;
}
