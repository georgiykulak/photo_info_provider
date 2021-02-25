#include <controller.hpp>

Controller::Controller (
    std::unique_ptr< IModel > modelPtr,
    std::unique_ptr< IView > viewPtr
)
    : m_modelPtr{ std::move( modelPtr ) }
    , m_viewPtr{ std::move( viewPtr ) }
{}

void Controller::fetchContent ()
{
    std::string username;
    m_viewPtr->readUsername( username );

	std::string password;
    m_viewPtr->readPassword( password );

	std::size_t index;
    m_viewPtr->readAssetNumber( index );

    m_modelPtr->fetch( username, password );

    m_modelPtr->setAssetNumber( index );

    m_modelPtr->parse();
}

void Controller::getResult () const noexcept
{
    m_viewPtr->get( m_modelPtr );
}