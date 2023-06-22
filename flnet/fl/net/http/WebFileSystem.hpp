#pragma once

#include "fl/net/http/Core.hpp"

namespace fl {

    struct WebFileMeta
    {
        std::string Name; MimeType Ext;
        std::string Relative;
        std::filesystem::path Base;

        // returns file name
        std::string File(bool extension = true) const {
            return Name + (extension
                             ? Ext.GetExtName(false)
                             : "");
        }
        // returns path to a file
        std::string FullPath() const {
            std::string temp = Base.string();
            temp.append(TargetPath());

            return  temp;
        }

        // returns target file name
        std::string TargetName(bool extension = true) const {
            return '/' + File(extension);
        }
        // returns relative path and file
        std::string TargetPath(bool extension = true) const {
            if (Relative == Base.filename())
                return TargetName(extension);

            return '/' + Relative + TargetName(extension);
        }

        bool operator==(WebFileMeta const& right) const 
        {
            return this->TargetPath() == right.TargetPath();
        }
    };

    class WebFilesSystem
    {
        // web documents directory
        std::string web_root_;
        // all stored files in web site 
        std::vector<WebFileMeta> files_;

        mutable std::shared_mutex mutex_;

    public:
        /**
         *  @param web_root is a directory where web documents stored
         */
        WebFilesSystem(std::string_view web_root);

        void SetWebRoot(std::string_view web_root);
        std::string_view GetWebRoot() const;

        // search file by name
        std::optional<WebFileMeta> FindByTargetName(std::string_view target, bool extension) const;
        // search file by target path
        std::optional<WebFileMeta> FindByTargetPath(std::string_view target, bool extension = true) const;

        bool IsTargetNameExist(std::string_view target, bool extension) const;  
        bool IsTargetPathExist(std::string_view target, bool extension) const;
    };

}