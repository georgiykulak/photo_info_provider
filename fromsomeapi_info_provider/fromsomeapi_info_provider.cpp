#include <iostream>
#include <curl\curl.h>

class Model
{
public:
	Model() = default;

	Model(std::string const& str)
	{
		set(str);
	}

	virtual void set(std::string const& str)
	{
		m_data = str;
	}

	virtual std::string const & get() const noexcept
	{
		return m_data;
	}

private:
	std::string m_data;
};

class IView
{
public:
	virtual void set(std::string &, std::string&) const = 0;
	
	virtual void get(Model const &) const noexcept = 0;
};

class CLIView final : public IView
{
public:
	void set(std::string& username, std::string& password) const override
	{
		std::cout << "Enter username: ";
		std::cin >> username;

		std::cout << "Enter password: ";
		std::cin >> password;
	}
	
	void get(Model const& model) const noexcept override
	{
		std::cout << model.get() << std::endl;
	}
};

class Controller
{
public:
	Controller() = delete;

	Controller( Model const & model, std::unique_ptr< IView > const & viewPtr )
		: m_model{ model }
		, m_view{ viewPtr }
	{}

	void getResult() const
	{
		m_view->get( m_model );
	}

private:
	Model const & m_model;
	std::unique_ptr< IView > const & m_view;
};

std::size_t WriteDataCallback(char* in, std::size_t size, std::size_t nmemb, std::string* out)
{
	if (!in)
		return 0;

	auto writeSize = size * nmemb;
	out->append(in, writeSize);

	return writeSize;
}

void send(Model& model, std::string const& link, std::string const& auth)
{
	CURL* curl = curl_easy_init();

	if (!curl)
		return;

	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(curl, CURLOPT_URL, link.data());

	struct curl_slist* headers = nullptr;

	headers = curl_slist_append(headers, auth.data());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteDataCallback);

	std::string response;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	model.set(response);
}

Model getModel(std::unique_ptr< IView > const& viewPtr, std::string const & apiLink)
{
	Model model;
	std::string user;
	std::string access_key;

	viewPtr->set( user, access_key );

	std::string const link = apiLink + "users/" + user + "/photos/";
	std::string const auth = "Authorization: Client-ID " + access_key;
	send(model, link, auth );

	if ( model.get().empty() )
		return Model("Error: Something wrong happened on curl_easy_init()");

	return model;
}

int main( int argc, char* argv[] )
{
	std::string const apiLink = "https://api.unsplash.com/";

	std::unique_ptr< IView > viewPtr( std::make_unique< CLIView >() );

	Model model = getModel(viewPtr, apiLink);

	Controller controller( model, viewPtr );

	controller.getResult();

	return 0;
}
