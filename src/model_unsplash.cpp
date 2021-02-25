#include <model_unsplash.hpp>

std::string ModelUnsplash::getApiLink () const
{
    return "https://api.unsplash.com/";
}

void ModelUnsplash::fetch (
    std::string const & user,
    std::string const & access_key
)
{
    std::string const link = getApiLink() + "users/" + user + "/photos/";
	std::string const auth = "Authorization: Client-ID " + access_key;
	set( sendAndGet( link, auth ) );
}

void ModelUnsplash::set ( std::string const & str )
{
    m_rawJSON = json::parse( str );
}

void ModelUnsplash::setAssetNumber ( std::size_t const index ) noexcept
{
    m_assetNumber = index;
}

void ModelUnsplash::parse ()
{
    json assetJSON;

    if (!m_rawJSON.is_array())
    {
        if (m_rawJSON.contains("errors") && m_rawJSON["errors"].is_array())
        {
            std::string str = m_rawJSON["errors"].at(0).get<std::string>();
            
            if (str.rfind("OAuth error", 0) == 0)
                m_response = { 401, "User is not authenticated" };
        }
        else
        {
            m_response = { 404, "Asset does not exist" };
        }
    
        return;
    }

    try
    {
        assetJSON = m_rawJSON.at(m_assetNumber);
    }
    catch (json::out_of_range const&)
    {
        m_response = { 404, "Asset does not exist" };
        return;
    }
    catch (std::exception const&)
    {
        m_response = { 404, "Asset does not exist" };
        return;
    }
    
    // Can NOT be null
    if (assetJSON.contains("id"))
        m_filename = assetJSON["id"].get< std::string >();

    // Can NOT be null
    if (assetJSON.contains("width") && assetJSON.contains("height"))
        m_filesize =
            assetJSON["width"].get< std::size_t >() *
            assetJSON["height"].get< std::size_t >();

    // Can NOT be null
    if (assetJSON.contains("created_at"))
        m_uploadTime = assetJSON["created_at"].get< std::string >();

    // Can NOT be null
    if (assetJSON.contains("updated_at"))
        m_modifiedTime = assetJSON["updated_at"].get< std::string >();

    // Can be null
    if (assetJSON.contains("description") && !assetJSON["description"].is_null())
        m_description = assetJSON["description"].get< std::string >();

    // Can NOT be null
    if (assetJSON.contains("urls") && assetJSON["urls"].contains("raw"))
        m_linkToPhoto = assetJSON["urls"]["raw"].get< std::string >();

    m_response = { getSuccessCode(), "The operation was successful" };
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
