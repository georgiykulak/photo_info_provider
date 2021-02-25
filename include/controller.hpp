#pragma once

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

	void fetchContent ();

	void getResult () const noexcept;

private:
	std::unique_ptr< IModel > m_modelPtr;
	std::unique_ptr< IView > m_viewPtr;
};
