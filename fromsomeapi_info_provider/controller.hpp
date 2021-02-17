#pragma once

#include "iview.h"

#include <memory>

class Controller
{
public:
	Controller() = delete;

	Controller(Model const& model, std::unique_ptr< IView > const& viewPtr)
		: m_model{ model }
		, m_view{ viewPtr }
	{}

	void setAssetNumber( std::size_t const index ) noexcept
	{
		m_view->setAssetNumber(index);
	}

	void getResult() const noexcept
	{
		m_view->get(m_model);
	}

private:
	Model const& m_model;
	std::unique_ptr< IView > const& m_view;
};
