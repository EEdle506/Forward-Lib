#pragma once

#include <string>
#include <map>

namespace fl {

    class MimeType 
    {
    public:
        enum Type 
        {
            Text = 0,
            App,
            Img,
            Audio,
            Video,
            Msg,
            Multi,
            Model,
            Example
        };

        enum SubType 
        {
            Unknown = 9,

            Plain,  
            Html,   // .html, .htm
            Css,
            Csv,    
            Php,
            JavaScript,
            Json,
            Xml,
            Pdf,
            Exe,
            Zip,
            Binary,
            Doc,
            Docx,
            Ppt,
            Pptx,
            Xls,
            Xlsx,
            Png,
            Jpeg,    // .jpg, .jpeg, .jpe, .jif, .jfif, .jfi
            Gif,
            Bmp,
            Ico,
            Svg,
            Mpeg,  // .mp3, .m4a, .m4b, .m4p, .mpga
            Mp4   // .mp4, .m4v
        };

    private:
        static const std::map<std::string_view, MimeType> mime_types_;

        Type type_;
        SubType sub_type_; 

        std::string ext_name_, sub_type_str_;

        MimeType(Type type, SubType sub_type, std::string_view format, std::string_view ext = "");
    public:
        MimeType();
        MimeType(std::string_view ext);

        /**
         *  @return 
         */
        std::string GetExtName(bool remove_dot = true) const;
        /**
         *  @return 
         */
        Type GetType() const;
        /**
         *  @return 
         */
        SubType GetSubType() const;
        /**
         *  @return 
         */
        std::string GetFormat() const;

        /**
         * 
         */
        bool IsUnknown() const;
        /**
         *  @return true if extension is valid
         */
        bool IsValid() const;

        /**
         *  @param ext extension names (txt, .txt, filename.txt)
         *  @return true if extension is valid
         */
        static bool HasExtension(std::string_view ext);

        /**
         *  @param ext extension names (txt, .txt, filename.txt)
         *  @return MimeType object. Can be valid or not depending on provided string
         */
        static MimeType FromString(std::string_view ext);

        /**
         *  Will try to remove existing extension from file 
         * 
         *  @param file file name with extension
         *  @return file without extension
         */
        static std::string RemoveExtension(std::string_view file);
        
    private:
        /**
         *  Removes all except extension 
         */
        static std::string_view ExtensionOnly(std::string_view str);
    };
}