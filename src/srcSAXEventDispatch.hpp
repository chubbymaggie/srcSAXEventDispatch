/**
 * @file srcSliceHandler.hpp
 *
 * @copyright Copyright (C) 2013-2014 SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef INCLUDED_SRCSAXEVENTDISPATCH_HPP
#define INCLUDED_SRCSAXEVENTDISPATCH_HPP

#include <srcSAXHandler.hpp>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <srcSAXEventDispatchUtilities.hpp>
#include <vector>
#include <memory>
namespace srcSAXEventDispatch {
    template <typename ...policies>
    class srcSAXEventDispatcher : public srcSAXHandler{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    std::unordered_map< std::string, std::function<void()>> process_map, process_map2;
    protected:
        void DispatchEvent(ParserState pstate, ElementState estate){
            ctx.DispatchEvent(pstate, estate);
        }
    public:
        srcSAXEventContext ctx;
        ~srcSAXEventDispatcher() {}
        srcSAXEventDispatcher(policies*... t2) : ctx(srcml_element_stack){
            ctx.elementListeners = {t2...};
            InitializeHandlers();
        }
        void InitializeHandlers(){
            process_map = {
                {"decl_stmt", [this](){
                    ++ctx.triggerField[ParserState::declstmt];
                    DispatchEvent(ParserState::declstmt, ElementState::open);
                } },
                { "expr_stmt", [this](){
                    ++ctx.triggerField[ParserState::exprstmt];
                    DispatchEvent(ParserState::exprstmt, ElementState::open);
                } },
                { "parameter_list", [this](){
                    ++ctx.triggerField[ParserState::parameterlist];
                    DispatchEvent(ParserState::parameterlist, ElementState::open);
                } },
                { "if", [this](){
                    ++ctx.triggerField[ParserState::ifstmt];
                    DispatchEvent(ParserState::ifstmt, ElementState::open);
                } },
                { "for", [this](){
                    ++ctx.triggerField[ParserState::forstmt];
                    DispatchEvent(ParserState::forstmt, ElementState::open);
                } },
                { "while", [this](){
                    ++ctx.triggerField[ParserState::whilestmt];
                    DispatchEvent(ParserState::whilestmt, ElementState::open);
                } },
                { "template", [this](){
                    ++ctx.triggerField[ParserState::templates];
                    DispatchEvent(ParserState::templates, ElementState::open);
                } },
                { "argument_list", [this](){
                    ++ctx.triggerField[ParserState::argumentlist];
                    DispatchEvent(ParserState::argumentlist, ElementState::open);
                } },
                { "call", [this](){
                    ++ctx.triggerField[ParserState::call];
                    DispatchEvent(ParserState::call, ElementState::open);
                } },
                { "function", [this](){
                    ++ctx.triggerField[ParserState::function];
                    DispatchEvent(ParserState::function, ElementState::open);
                } },
                { "constructor", [this](){
                    ++ctx.triggerField[ParserState::constructor];
                    DispatchEvent(ParserState::constructor, ElementState::open);
                } },
                { "function_decl", [this](){
                    ++ctx.triggerField[ParserState::functiondecl];
                    DispatchEvent(ParserState::functiondecl, ElementState::open);
                } },
                { "destructor_decl", [this](){
                    ++ctx.triggerField[ParserState::destructordecl];
                    DispatchEvent(ParserState::destructordecl, ElementState::open);
                } },
                { "constructor_decl", [this](){
                    ++ctx.triggerField[ParserState::constructordecl];
                    DispatchEvent(ParserState::constructordecl, ElementState::open);
                } },
                { "class", [this](){
                    ++ctx.triggerField[ParserState::classn];
                    DispatchEvent(ParserState::classn, ElementState::open);
                } },
                { "struct", [this](){
                    ++ctx.triggerField[ParserState::classn];
                    DispatchEvent(ParserState::structn, ElementState::open);
                } },
                { "super_list", [this](){
                    ++ctx.triggerField[ParserState::super_list];
                    DispatchEvent(ParserState::super_list, ElementState::open);
                } },
                { "super", [this](){
                    ++ctx.triggerField[ParserState::super];
                    DispatchEvent(ParserState::super, ElementState::open);
                } },
                { "public", [this](){
                    ++ctx.triggerField[ParserState::publicaccess];
                    DispatchEvent(ParserState::publicaccess, ElementState::open);
                } },
                { "protected", [this](){
                    ++ctx.triggerField[ParserState::protectedaccess];
                    DispatchEvent(ParserState::protectedaccess, ElementState::open);
                } },
                { "private", [this](){
                    ++ctx.triggerField[ParserState::privateaccess];
                    DispatchEvent(ParserState::privateaccess, ElementState::open);
                } },
                { "destructor", [this](){
                    ++ctx.triggerField[ParserState::destructor];
                    DispatchEvent(ParserState::destructor, ElementState::open);
                } },
                { "parameter", [this](){
                    ++ctx.triggerField[ParserState::parameter];
                    DispatchEvent(ParserState::parameter, ElementState::open);
                } },                
                { "member_list", [this](){
                    ++ctx.triggerField[ParserState::memberlist];
                    DispatchEvent(ParserState::memberlist, ElementState::open);
                } },
                { "index", [this](){
                    ++ctx.triggerField[ParserState::index];
                    DispatchEvent(ParserState::index, ElementState::open);
                } },
                { "operator", [this](){
                    ++ctx.triggerField[ParserState::op];
                    DispatchEvent(ParserState::op, ElementState::open);
                } },
                { "block", [this](){ 
                    ++ctx.triggerField[ParserState::block];
                    DispatchEvent(ParserState::block, ElementState::open);
                } },
                { "init", [this](){
                    ++ctx.triggerField[ParserState::init];
                    DispatchEvent(ParserState::init, ElementState::open);
                } },
                { "argument", [this](){
                    ++ctx.triggerField[ParserState::argument];
                    DispatchEvent(ParserState::argument, ElementState::open);
                } },
                { "literal", [this](){
                    ++ctx.triggerField[ParserState::literal];
                    DispatchEvent(ParserState::literal, ElementState::open);
                } },
                { "modifier", [this](){
                    ++ctx.triggerField[ParserState::modifier];
                    DispatchEvent(ParserState::modifier, ElementState::open);
                } },
                { "decl", [this](){
                    ++ctx.triggerField[ParserState::decl]; 
                    DispatchEvent(ParserState::decl, ElementState::open);
                } },
                { "type", [this](){
                    ++ctx.triggerField[ParserState::type]; 
                    DispatchEvent(ParserState::type, ElementState::open);
                } },
                { "typedef", [this](){
                    ++ctx.triggerField[ParserState::typedefexpr]; 
                    DispatchEvent(ParserState::typedefexpr, ElementState::open);
                } },          
                { "expr", [this](){
                    ++ctx.triggerField[ParserState::expr];
                    DispatchEvent(ParserState::expr, ElementState::open);
                } },
                { "name", [this](){
                    ++ctx.triggerField[ParserState::name];
                    DispatchEvent(ParserState::name, ElementState::open);
                } },
                { "macro", [this](){
                    ++ctx.triggerField[ParserState::macro];
                    DispatchEvent(ParserState::macro, ElementState::open);
                } },
                { "specifier", [this](){
                    ++ctx.triggerField[ParserState::specifier];
                    DispatchEvent(ParserState::specifier, ElementState::open);
                } }
            };
            process_map2 = {
                {"decl_stmt", [this](){
                    --ctx.triggerField[ParserState::declstmt];
                    DispatchEvent(ParserState::declstmt, ElementState::close);
                } },             
                { "expr_stmt", [this](){
                    --ctx.triggerField[ParserState::exprstmt];
                    DispatchEvent(ParserState::exprstmt, ElementState::close);
                } },            
                { "parameter_list", [this](){
                    --ctx.triggerField[ParserState::parameterlist];
                    DispatchEvent(ParserState::parameterlist, ElementState::close);
                } },            
                { "if", [this](){
                    --ctx.triggerField[ParserState::ifstmt];
                    DispatchEvent(ParserState::ifstmt, ElementState::close);
                } },            
                { "for", [this](){
                    --ctx.triggerField[ParserState::forstmt];
                    DispatchEvent(ParserState::forstmt, ElementState::close);
                } },            
                { "while", [this](){
                    --ctx.triggerField[ParserState::whilestmt];
                    DispatchEvent(ParserState::whilestmt, ElementState::close);
                } },
                { "template", [this](){
                    --ctx.triggerField[ParserState::templates];
                    DispatchEvent(ParserState::templates, ElementState::close);
                } },            
                { "argument_list", [this](){
                    if(!ctx.genericDepth.empty()){
                        std::cerr<<ctx.genericDepth.back()<<" "<<ctx.depth<<std::endl;
                        if(ctx.genericDepth.back() == ctx.depth){
                            --ctx.triggerField[ParserState::genericargumentlist];
                            ctx.genericDepth.pop_back();
                        }
                    }
                    --ctx.triggerField[ParserState::argumentlist];
                    DispatchEvent(ParserState::argumentlist, ElementState::close);
                } },            
                { "call", [this](){
                    --ctx.triggerField[ParserState::call];
                    DispatchEvent(ParserState::call, ElementState::close);
                } },            
                { "function", [this](){
                    --ctx.triggerField[ParserState::function];
                    DispatchEvent(ParserState::function, ElementState::close);
                } },
                { "constructor", [this](){
                    --ctx.triggerField[ParserState::constructor];
                    DispatchEvent(ParserState::constructor, ElementState::close);
                } },
                { "destructor", [this](){
                    --ctx.triggerField[ParserState::destructor];
                    DispatchEvent(ParserState::destructor, ElementState::close);
                } },
                { "function_decl", [this](){
                    --ctx.triggerField[ParserState::functiondecl];
                    DispatchEvent(ParserState::functiondecl, ElementState::close);
                } },
                { "constructor_decl", [this](){
                    --ctx.triggerField[ParserState::constructordecl];
                    DispatchEvent(ParserState::constructordecl, ElementState::close);
                } },
                { "destructor_decl", [this](){
                    --ctx.triggerField[ParserState::destructordecl];
                    DispatchEvent(ParserState::destructordecl, ElementState::close);
                } },
                { "class", [this](){
                    --ctx.triggerField[ParserState::classn];
                    DispatchEvent(ParserState::classn, ElementState::close);
                } },
                { "struct", [this](){
                    --ctx.triggerField[ParserState::classn];
                    DispatchEvent(ParserState::structn, ElementState::close);
                } },
                { "super_list", [this](){
                    ++ctx.triggerField[ParserState::super_list];
                    DispatchEvent(ParserState::super_list, ElementState::close);
                } },
                { "super", [this](){
                    ++ctx.triggerField[ParserState::super];
                    DispatchEvent(ParserState::super, ElementState::close);
                } },
                { "public", [this](){
                    ++ctx.triggerField[ParserState::publicaccess];
                    DispatchEvent(ParserState::publicaccess, ElementState::close);
                } },
                { "protected", [this](){
                    ++ctx.triggerField[ParserState::protectedaccess];
                    DispatchEvent(ParserState::protectedaccess, ElementState::close);
                } },
                { "private", [this](){
                    ++ctx.triggerField[ParserState::privateaccess];
                    DispatchEvent(ParserState::privateaccess, ElementState::close);
                } },
                { "parameter", [this](){
                    --ctx.triggerField[ParserState::parameterlist];
                    DispatchEvent(ParserState::parameter, ElementState::close);
                } },    
                { "member_list", [this](){
                    --ctx.triggerField[ParserState::memberlist];
                    DispatchEvent(ParserState::memberlist, ElementState::close);
                } },    
                { "index", [this](){
                    --ctx.triggerField[ParserState::index];
                    DispatchEvent(ParserState::index, ElementState::close);
                } },    
                { "operator", [this](){
                    --ctx.triggerField[ParserState::op];
                    DispatchEvent(ParserState::op, ElementState::close);
                } },
                { "block", [this](){ 
                    --ctx.triggerField[ParserState::block];
                    DispatchEvent(ParserState::block, ElementState::close);
                } },
                { "init", [this](){
                    --ctx.triggerField[ParserState::init];
                    DispatchEvent(ParserState::init, ElementState::close);
                } },    
                { "argument", [this](){
                    --ctx.triggerField[ParserState::argument];
                    DispatchEvent(ParserState::argument, ElementState::close);
                } },    
                { "literal", [this](){
                    --ctx.triggerField[ParserState::literal];
                    DispatchEvent(ParserState::literal, ElementState::close);
                } },    
                { "modifier", [this](){
                    --ctx.triggerField[ParserState::modifier];
                    DispatchEvent(ParserState::modifier, ElementState::close);
                } },    
                { "decl", [this](){
                    --ctx.triggerField[ParserState::decl]; 
                    DispatchEvent(ParserState::decl, ElementState::close);
                } },    
                { "type", [this](){
                    --ctx.triggerField[ParserState::type];
                    DispatchEvent(ParserState::type, ElementState::close);
                } },
                { "typedef", [this](){
                    --ctx.triggerField[ParserState::typedefexpr]; 
                    DispatchEvent(ParserState::typedefexpr, ElementState::close);
                } },    
                { "expr", [this](){
                    --ctx.triggerField[ParserState::expr];
                    DispatchEvent(ParserState::expr, ElementState::close);
                } },    
                { "name", [this](){
                    --ctx.triggerField[ParserState::name];
                    DispatchEvent(ParserState::name, ElementState::close);
                } },
                { "macro", [this](){
                    --ctx.triggerField[ParserState::macro];
                    DispatchEvent(ParserState::macro, ElementState::close);
                } },
                { "tokenstring", [this](){
                    ctx.triggerField[ParserState::tokenstring] = 1;
                    DispatchEvent(ParserState::tokenstring, ElementState::close);
                    ctx.triggerField[ParserState::tokenstring] = 0;
                } },
                { "specifier", [this](){
                    --ctx.triggerField[ParserState::specifier];
                    DispatchEvent(ParserState::specifier, ElementState::close);
                } }
            };            
        }

        /*
        virtual void startDocument() {}
        virtual void endDocument() {}
        */
    
        /**
        * startRoot
        * @param localname the name of the element tag
        * @param prefix the tag prefix
        * @param URI the namespace of tag
        * @param nb_namespaces number of namespaces definitions
        * @param namespaces the defined namespaces
        * @param nb_attributes the number of attributes on the tag
        * @param nb_defaulted the number of defaulted attributes
        * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
        *
        * SAX handler function for start of the root element.
        * Counts the root unit (if an archive, to avoid double count with startUnit).
        * Overide for desired behaviour.
        */
        virtual void startRoot(const char * localname, const char * prefix, const char * URI,
                            int num_namespaces, const struct srcsax_namespace * namespaces, int num_attributes,
                            const struct srcsax_attribute * attributes) {
            
        }
        /**
        * startUnit
        * @param localname the name of the element tag
        * @param prefix the tag prefix
        * @param URI the namespace of tag
        * @param nb_namespaces number of namespaces definitions
        * @param namespaces the defined namespaces
        * @param nb_attributes the number of attributes on the tag
        * @param nb_defaulted the number of defaulted attributes
        * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
        *
        * SAX handler function for start of an unit.
        * Counts each unit tag (= filecount non-archive, = filecount + 1 if archive).
        * Overide for desired behaviour.
        */
        virtual void startUnit(const char * localname, const char * prefix, const char * URI,
                            int num_namespaces, const struct srcsax_namespace * namespaces, int num_attributes,
                            const struct srcsax_attribute * attributes) {
            if(num_attributes >= 3){
                ctx.currentFilePath = std::string(attributes[2].value);
                ctx.currentFileLanguage = std::string(attributes[1].value);
                ctx.currentsrcMLRevision = std::string(attributes[0].value);
            }
        }
        /**
        * startElementNs
        * @param localname the name of the element tag
        * @param prefix the tag prefix
        * @param URI the namespace of tag
        * @param nb_namespaces number of namespaces definitions
        * @param namespaces the defined namespaces
        * @param nb_attributes the number of attributes on the tag
        * @param nb_defaulted the number of defaulted attributes
        * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
        *
        * SAX handler function for start of an element.
        * Overide for desired behaviour.
        */
        virtual void startElement(const char * localname, const char * prefix, const char * URI,
                                    int num_namespaces, const struct srcsax_namespace * namespaces, int num_attributes,
                                    const struct srcsax_attribute * attributes) {

            ++ctx.depth;

            if(std::string(localname) == "position"){
                ctx.currentLineNumber = strtoul(attributes[0].value, NULL, 0);
            }
            std::string name;
            if(num_attributes){
                name = attributes[0].value;
            }
            if(name == "generic" && std::string(localname) == "argument_list"){
                ctx.genericDepth.push_back(ctx.depth);
                ++ctx.triggerField[ParserState::genericargumentlist];
            }
            if(std::string(localname) != ""){
                std::unordered_map<std::string, std::function<void()>>::const_iterator process = process_map.find(localname);            
                if (process != process_map.end()) {
                    process->second();
                }
            }
        }
        /**
        * charactersUnit
        * @param ch the characers
        * @param len number of characters
        *
        * SAX handler function for character handling within a unit.
        * Overide for desired behaviour.
        */
        virtual void charactersUnit(const char * ch, int len) {
            ctx.currentToken.clear();
            ctx.currentToken.append(ch, len);
            std::unordered_map<std::string, std::function<void()>>::const_iterator process = process_map2.find("tokenstring");
            process->second();
        }
    
        // end elements may need to be used if you want to collect only on per file basis or some other granularity.
        virtual void endRoot(const char * localname, const char * prefix, const char * URI) {
    
        }
        virtual void endUnit(const char * localname, const char * prefix, const char * URI) {
    
        }
    
        virtual void endElement(const char * localname, const char * prefix, const char * URI) {

            std::unordered_map<std::string, std::function<void()>>::const_iterator process2 = process_map2.find(localname);            
            if (process2 != process_map2.end()) {
                process2->second();
            }

            --ctx.depth;

        }
    #pragma GCC diagnostic pop
    
    };
}
#endif