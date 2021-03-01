#include <model_unsplash.hpp>

#include <iostream>

void ModelUnsplash::fetch (
    std::string const & user,
    std::string const & access_key
)
{
    std::string const endPoint =
        s_apiLink.data() + ( "users/" + user + "/photos/" );
	std::string const authHeader = "Authorization: Client-ID " + access_key;
    
    std::string responce;
    sendGetRequest( responce, endPoint, authHeader );
	set( responce );
}

void ModelUnsplash::set ( std::string const & str )
{
    if ( !str.empty() )
        m_rawJSON = json::parse( str );
}

void ModelUnsplash::setAssetNumber ( std::size_t const index ) noexcept
{
    m_assetNumber = index;
}

void ModelUnsplash::parse ()
try
{
    json assetJSON;

    if ( m_rawJSON.empty() )
    {
        m_response = { 501, "Not Implemented" };
        return;
    }

    if ( !m_rawJSON.is_array() )
    {
        if ( m_rawJSON.contains( "errors" ) &&
            m_rawJSON[ "errors" ].is_array() &&
            !m_rawJSON[ "errors" ].empty()
        )
        {
            std::string str =
                m_rawJSON[ "errors" ].at( 0 ).get< std::string >();
            
            if ( str.rfind( "OAuth error", 0 ) == 0 )
                m_response = { 401, "User is not authenticated" };
        }
        else
        {
            m_response = { 404, "Asset does not exist" };
        }
    
        return;
    }

    if ( m_rawJSON.size() <= m_assetNumber )
    {
        m_response = { 404, "Asset does not exist" };
        return;
    }
    
    assetJSON = m_rawJSON.at( m_assetNumber );
    
    if ( assetJSON.contains( "id" ) && !assetJSON[ "id" ].is_null() )
        m_filename = assetJSON[ "id" ].get< std::string >();

    if ( assetJSON.contains( "width" ) && assetJSON.contains( "height" ) &&
        !assetJSON[ "width" ].is_null() && !assetJSON[ "height" ].is_null()
    )
        m_filesize =
            assetJSON[ "width" ].get< std::size_t >() *
            assetJSON[ "height" ].get< std::size_t >();

    if ( assetJSON.contains( "created_at" ) &&
        !assetJSON[ "created_at" ].is_null()
    )
        m_uploadTime = assetJSON[ "created_at" ].get< std::string >();

    if ( assetJSON.contains( "updated_at" ) &&
        !assetJSON[ "updated_at" ].is_null()
    )
        m_modifiedTime = assetJSON[ "updated_at" ].get< std::string >();

    if ( assetJSON.contains( "description" ) &&
        !assetJSON[ "description" ].is_null()
    )
        m_description = assetJSON[ "description" ].get< std::string >();

    if ( assetJSON.contains( "urls" ) && !assetJSON[ "urls" ].is_null() &&
        assetJSON["urls"].contains("raw") &&
        !assetJSON[ "urls" ][ "raw" ].is_null()
    )
        m_linkToPhoto = assetJSON[ "urls" ][ "raw" ].get< std::string >();

    m_response = { getSuccessCode(), "The operation was successful" };
}
catch ( std::exception const & ex )
{
    m_response = { 500, "Internal Server Error" };
}

unsigned ModelUnsplash::getSuccessCode () const noexcept
{
    return 200;
}

std::pair< unsigned, std::string > const & ModelUnsplash::getResponse () const noexcept
{
    return m_response;
}

std::string const & ModelUnsplash::getFilename () const noexcept
{
    return m_filename;
}

std::size_t ModelUnsplash::getFilesize () const noexcept
{
    return m_filesize;
}

std::string const & ModelUnsplash::getModifiedTime () const noexcept
{
    return m_modifiedTime;
}

std::string const & ModelUnsplash::getUploadTime () const noexcept
{
    return m_uploadTime;
}

std::string const & ModelUnsplash::getDescription () const noexcept
{
    return m_description;
}

std::string const & ModelUnsplash::getLinkToPhoto () const noexcept
{
    return m_linkToPhoto;
}
