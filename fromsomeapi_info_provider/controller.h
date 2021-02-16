#pragma once

#include "iview.h"

#include <memory>

class Controller
{
public:
	Controller() = delete;

	Controller(Model const& model, std::unique_ptr< IView > const& viewPtr);

	void getResult() const noexcept;

private:
	Model const& m_model;
	std::unique_ptr< IView > const& m_view;
};
