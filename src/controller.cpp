#include <controller.hpp>

Controller::Controller (
    std::unique_ptr< IModel > modelPtr,
    std::unique_ptr< IView > viewPtr
)
    : m_modelPtr{ std::move( modelPtr ) }
    , m_viewPtr{ std::move( viewPtr ) }
{}

void Controller::setDetails ()
{
    m_viewPtr->readUsername( m_username );
    m_viewPtr->readPassword( m_password );
    m_viewPtr->readAssetNumber( m_index );
}

void Controller::fetch ()
{
    m_modelPtr->fetch( m_username, m_password );
}

void Controller::prepareResult ()
{
    m_modelPtr->setAssetNumber( m_index );

    m_modelPtr->parse();
}

void Controller::fetchContent ()
{
    setDetails();
    fetch();
    prepareResult();
}

void Controller::getResult () const noexcept
{
    m_viewPtr->get( m_modelPtr );
}