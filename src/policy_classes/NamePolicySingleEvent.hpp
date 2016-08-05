#include <srcSAXEventDispatchUtilities.hpp>

#include <TypePolicySingleEvent.hpp>
#include <TemplateArgumentPolicySingleEvent.hpp>

#include <string>
#include <vector>
#include <iostream>

#ifndef INCLUDED_NAME_POLICY_SINGLE_EVENT_HPP
#define INCLUDED_NAME_POLICY_SINGLE_EVENT_HPP

class NamePolicy : public srcSAXEventDispatch::EventListener, public srcSAXEventDispatch::PolicyDispatcher, public srcSAXEventDispatch::PolicyListener {

public:

    struct NameData {

        std::string name;
        std::vector<NameData *> names;
        std::vector<TemplateArgumentPolicy::TemplateArgumentData *> templateArguments;
        std::vector<std::string> arrayIndices;

        friend std::ostream & operator<<(std::ostream & out, const NameData & nameData) {

            if(!nameData.name.empty()) {
                out << nameData.name;
            }

            for(size_t pos = 0; pos < nameData.names.size(); ++pos) {

                if(pos != 0) out << "::";
                out << (*nameData.names[pos]);

            }

            if(!nameData.templateArguments.empty()) {
                out << '<';
                for(const TemplateArgumentPolicy::TemplateArgumentData * arg : nameData.templateArguments) {
                    out << *arg;
                }
                out << '>';
            }

            for(const std::string & index : nameData.arrayIndices) {
                out << '[' << index << ']';
            }

            return out;


        }

    };

private:

    NameData data;
    std::size_t nameDepth;

    NamePolicy * namePolicy;
    TemplateArgumentPolicy * templateArgumentPolicy;

public:


    NamePolicy(std::initializer_list<srcSAXEventDispatch::PolicyListener *> listeners)
        : srcSAXEventDispatch::PolicyDispatcher(listeners),
          data{},
          nameDepth(0),
          namePolicy(nullptr),
          templateArgumentPolicy(nullptr) { 
    
        InitializeNamePolicyHandlers();

    }

    ~NamePolicy() {

        if(namePolicy) delete namePolicy;
        if(templateArgumentPolicy) delete templateArgumentPolicy;

    }

protected:
    void * DataInner() const override {

        return new NameData(data);

    }
    virtual void Notify(const PolicyDispatcher * policy, const srcSAXEventDispatch::srcSAXEventContext & ctx) override {

        if(typeid(NamePolicy) == typeid(*policy)) {

            data.names.push_back(policy->Data<NameData>());
            ctx.dispatcher->RemoveListener(nullptr);

        } else if(typeid(TemplateArgumentPolicy) == typeid(*policy)) {

            data.templateArguments.push_back(policy->Data<TemplateArgumentPolicy::TemplateArgumentData>());
            ctx.dispatcher->RemoveListener(nullptr);

        }

    }

private:

    void InitializeNamePolicyHandlers() {
        using namespace srcSAXEventDispatch;

        // start of policy
        openEventMap[ParserState::name] = [this](srcSAXEventContext& ctx) {

            if(!nameDepth) {

                nameDepth = ctx.depth;
                data = NameData{};

                CollectTemplateArgumentsHandlers();
                CollectArrayIndicesHandlers();

            } else if((nameDepth + 1) == ctx.depth) {

                NopCloseEvents({ParserState::tokenstring});
                if(!namePolicy) namePolicy = new NamePolicy{this};
                ctx.dispatcher->AddListenerDispatch(namePolicy); 

            }

        };

        // end of policy
        closeEventMap[ParserState::name] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && nameDepth == ctx.depth) {

                nameDepth = 0;
 
                NotifyAll(ctx);
                InitializeNamePolicyHandlers();

            }
           
        };

        closeEventMap[ParserState::tokenstring] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && nameDepth == ctx.depth) {

                data.name += ctx.currentToken;

            }

        };

    }

    void CollectTemplateArgumentsHandlers() {
        using namespace srcSAXEventDispatch;

        openEventMap[ParserState::genericargumentlist] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && (nameDepth + 1) == ctx.depth) {

                openEventMap[ParserState::argument] = [this](srcSAXEventContext& ctx) {

                    if(nameDepth && (nameDepth + 2) == ctx.depth) {

                        if(!templateArgumentPolicy) templateArgumentPolicy = new TemplateArgumentPolicy{this};
                        ctx.dispatcher->AddListenerDispatch(templateArgumentPolicy);

                    }

                };

            }

        };

        closeEventMap[ParserState::genericargumentlist] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && (nameDepth + 1) == ctx.depth) {

                NopOpenEvents({ParserState::argument});

            }

        };

    }

    void CollectArrayIndicesHandlers() {
        using namespace srcSAXEventDispatch;

        openEventMap[ParserState::index] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && (nameDepth + 1) == ctx.depth) {

                data.arrayIndices.push_back(std::string());

            }

        };

        closeEventMap[ParserState::index] = [this](srcSAXEventContext& ctx) {

            if(nameDepth && (nameDepth + 1) == ctx.depth) {

                NopOpenEvents({ParserState::expr});
                NopCloseEvents({ParserState::expr});

            }

        };

        openEventMap[ParserState::expr] = [this](srcSAXEventContext& ctx) {

            size_t num_elements = ctx.elementStack.size();
            if(nameDepth && (nameDepth + 2) == ctx.depth && num_elements > 1 && ctx.elementStack[num_elements - 2] == "index") {

                closeEventMap[ParserState::tokenstring] = [this](srcSAXEventContext& ctx) { data.arrayIndices.back() += ctx.currentToken; };

            }

        };

        closeEventMap[ParserState::expr] = [this](srcSAXEventContext& ctx) {

            size_t num_elements = ctx.elementStack.size();
            if(nameDepth && (nameDepth + 2) == ctx.depth && num_elements > 0 && ctx.elementStack.back() == "index") {

                NopCloseEvents({ParserState::tokenstring});

            }

        };

    }

};

#endif
