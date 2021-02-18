#pragma once

#include "iview.h"
#include "imodel.h"

#include <memory>

class Controller
{
public:
	Controller() = delete;

	Controller(std::unique_ptr< IModel > & modelPtr, std::unique_ptr< IView > const& viewPtr)
		: m_modelPtr{ modelPtr }
		, m_viewPtr{ viewPtr }
	{}

	void chooseAsset( std::size_t const index )
	{
		m_modelPtr->setAssetNumber(index);

		m_modelPtr->parse();
	}

	void getResult() const noexcept
	{
		m_viewPtr->get(m_modelPtr);
	}

private:
	std::unique_ptr< IModel > & m_modelPtr;
	std::unique_ptr< IView > const& m_viewPtr;
};
