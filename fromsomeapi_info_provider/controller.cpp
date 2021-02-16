#include "controller.h"

Controller::Controller(Model const& model, std::unique_ptr< IView > const& viewPtr)
	: m_model{ model }
	, m_view{ viewPtr }
{}

void Controller::getResult() const noexcept
{
	m_view->get(m_model);
}