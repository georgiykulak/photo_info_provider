#ifndef PHOTO_INFO_PROVIDER_CONTROLLER_HPP
#define PHOTO_INFO_PROVIDER_CONTROLLER_HPP

#include <iview.hpp>

#include <memory>

class Controller
{
public:
	Controller () = delete;

	Controller (
		std::unique_ptr< IModel > modelPtr,
		std::unique_ptr< IView > viewPtr
	);

	void setDetails ();

	void fetch ();

	void prepareResult ();

	void fetchContent ();

	void getResult () const noexcept;

private:
	std::unique_ptr< IModel > m_modelPtr;
	std::unique_ptr< IView > m_viewPtr;
	std::string m_username;
	std::string m_password;
	std::size_t m_index;
};

#endif // PHOTO_INFO_PROVIDER_CONTROLLER_HPP //
