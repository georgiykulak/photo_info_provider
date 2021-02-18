#pragma once

#include "iview.h"
#include "imodel.h"

#include <memory>

class Controller
{
public:
	Controller() = delete;

	Controller(std::unique_ptr< IModel >&& modelPtr, std::unique_ptr< IView >&& viewPtr)
		: m_modelPtr{ std::move( modelPtr ) }
		, m_viewPtr{ std::move( viewPtr ) }
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
	std::unique_ptr< IModel > m_modelPtr;
	std::unique_ptr< IView > m_viewPtr;
};
