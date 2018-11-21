#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <sstream>

using std::string;

static const string graph_str = "Reservoir-55 -> Junction-80\n"
                                "Reservoir-58 -> AgricultureDemand-0\n"
                                "Reservoir-58 -> HumanDemand-1\n"
                                "Reservoir-58 -> HumanDemand-2\n"
                                "Reservoir-57 -> Junction-80\n"
                                "Reservoir-56 -> Junction-80\n"
                                "Reservoir-63 -> Reservoir-64\n"
                                "Reservoir-64 -> Reservoir-65\n"
                                "Reservoir-65 -> Reservoir-66\n"
                                "Reservoir-68 -> Reservoir-69\n"
                                "Reservoir-56 -> AnimalDemand-6\n"
                                "Reservoir-56 -> AgricultureDemand-7\n"
                                "Reservoir-56 -> HumanDemand-8\n"
                                "Reservoir-54 -> HumanDemand-9\n"
                                "Reservoir-54 -> AgricultureDemand-10\n"
                                "Reservoir-54 -> AnimalDemand-11\n"
                                "Reservoir-60 -> AnimalDemand-14\n"
                                "Reservoir-60 -> HumanDemand-15\n"
                                "Reservoir-60 -> AgricultureDemand-16\n"
                                "Reservoir-55 -> HumanDemand-5\n"
                                "Reservoir-55 -> AgricultureDemand-4\n"
                                "Reservoir-55 -> AnimalDemand-3\n"
                                "Reservoir-57 -> AnimalDemand-12\n"
                                "Reservoir-57 -> HumanDemand-13\n"
                                "Reservoir-54 -> Reservoir-55\n"
                                "Junction-81 -> Reservoir-56\n"
                                "Junction-82 -> Reservoir-57\n"
                                "Junction-80 -> Reservoir-58\n"
                                "Reservoir-60 -> HumanDemand-23\n"
                                "Reservoir-57 -> AgricultureDemand-26\n"
                                "Reservoir-61 -> DrainDemand-27\n"
                                "Reservoir-60 -> DrainDemand-28\n"
                                "Reservoir-61 -> Reservoir-62\n"
                                "Junction-83 -> Reservoir-54\n"
                                "Junction-84 -> Junction-83\n"
                                "Reservoir-73 -> AnimalDemand-29\n"
                                "Reservoir-73 -> HumanDemand-30\n"
                                "Reservoir-73 -> AgricultureDemand-31\n"
                                "Reservoir-58 -> Reservoir-73\n"
                                "Reservoir-73 -> Junction-85\n"
                                "Junction-85 -> DrainDemand-32\n"
                                "Junction-86 -> Reservoir-60\n"
                                "Reservoir-58 -> AnimalDemand-33\n"
                                "Reservoir-69 -> Junction-87\n"
                                "Junction-87 -> Reservoir-70\n"
                                "Junction-87 -> Reservoir-60\n"
                                "Reservoir-67 -> Junction-88\n"
                                "Junction-88 -> Reservoir-68\n"
                                "Junction-88 -> HumanDemand-22\n"
                                "Reservoir-70 -> Junction-89\n"
                                "Junction-89 -> Reservoir-71\n"
                                "Junction-89 -> HumanDemand-21\n"
                                "Junction-89 -> HumanDemand-20\n"
                                "Reservoir-71 -> Junction-90\n"
                                "Junction-90 -> Reservoir-72\n"
                                "Junction-90 -> HumanDemand-19\n"
                                "Junction-90 -> HumanDemand-18\n"
                                "Reservoir-72 -> Junction-91\n"
                                "Junction-91 -> Reservoir-59\n"
                                "Junction-91 -> HumanDemand-17\n"
                                "Reservoir-74 -> AgricultureDemand-34\n"
                                "Reservoir-74 -> AgricultureDemand-35\n"
                                "Reservoir-74 -> AnimalDemand-36\n"
                                "Reservoir-74 -> HumanDemand-37\n"
                                "Reservoir-77 -> HumanDemand-38\n"
                                "Reservoir-77 -> AnimalDemand-39\n"
                                "Reservoir-77 -> AgricultureDemand-40\n"
                                "Junction-92 -> Reservoir-76\n"
                                "Reservoir-76 -> AgricultureDemand-41\n"
                                "Reservoir-76 -> IndustrialDemand-42\n"
                                "Reservoir-76 -> HumanDemand-43\n"
                                "Reservoir-77 -> HumanDemand-43\n"
                                "Reservoir-76 -> HumanDemand-44\n"
                                "Reservoir-76 -> AnimalDemand-45\n"
                                "Reservoir-75 -> Reservoir-77\n"
                                "Reservoir-75 -> HumanDemand-46\n"
                                "Reservoir-75 -> AnimalDemand-47\n"
                                "Reservoir-75 -> AgricultureDemand-48\n"
                                "Reservoir-77 -> Junction-93\n"
                                "Reservoir-76 -> Junction-93\n"
                                "Junction-93 -> DrainDemand-49\n"
                                "Reservoir-74 -> Junction-94\n"
                                "Junction-94 -> DrainDemand-50\n"
                                "Reservoir-66 -> Junction-95\n"
                                "Junction-95 -> Reservoir-67\n"
                                "Junction-95 -> Reservoir-74\n"
                                "Reservoir-59 -> Junction-96\n"
                                "Junction-96 -> Junction-83\n"
                                "Junction-97 -> Reservoir-74\n"
                                "Reservoir-62 -> Junction-98\n"
                                "Junction-98 -> Reservoir-63\n"
                                "Junction-98 -> HumanDemand-53\n"
                                "Junction-96 -> HumanDemand-25\n"
                                "Junction-96 -> HumanDemand-24\n"
                                "Junction-85 -> HumanDemand-52\n"
                                "Junction-96 -> Reservoir-79\n"
                                "Reservoir-79 -> Reservoir-78\n"
                                "Reservoir-78 -> Junction-99\n"
                                "Junction-99 -> Reservoir-75\n"
                                "Junction-99 -> HumanDemand-51\n"
                                "Junction-100 -> Reservoir-78\n";


using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::queue;
using std::shared_ptr;
using std::stringstream;

enum class ElementType {Node, Link};
struct Link;

using SPtrLink = shared_ptr<Link>;
struct Element {string name; unsigned int id; ElementType type; unsigned int getId() { return this->id; } virtual ~Element(){}};
using SPtrElement = shared_ptr<Element>;
using VectorOfElements = vector<SPtrElement>;
using VectorOfLinks = vector<SPtrLink>;

struct Node: public Element {VectorOfLinks upstreamLinks; VectorOfLinks downstreamLinks; VectorOfLinks &getUpstreamLinks(){return this->upstreamLinks;} VectorOfLinks &getDownstreamLinks(){return this->downstreamLinks;}};
using SPtrNode = std::shared_ptr<Node>;
struct Link : public Element {SPtrNode src; SPtrNode dst; SPtrNode getDownstream(){return this->dst;} SPtrNode getUpstream(){return this->src;}};

using VectorOfNodes = vector<SPtrNode>;

VectorOfElements levelOrder(const VectorOfElements &elements);
VectorOfNodes filterByEnabledNodes(const VectorOfElements &elements);
VectorOfElements load(const string &str);
using VectorOfString = vector<string>;

int main()
{
    VectorOfElements elements = load(graph_str);
    VectorOfElements order = levelOrder(elements);
    for (auto element: order)
    {
        cout << "(" << element->name << ":" << element->getId() << ")" << endl;
    }
    return 0;
}

VectorOfString split(const string &s, char delim)
{
  stringstream ss(s);
  string item;
  VectorOfString elems;
  while (std::getline(ss, item, delim))
  {
    elems.emplace_back(std::move(item));
  }
  return elems;
}

VectorOfElements load(const string &str)
{
    VectorOfElements result;
    VectorOfString lines = split(str, '\n');
    string src, del, dst;
    int linkID = 0;
    for (auto &line : lines)
    {
        stringstream ss(line);
        ss >> src >> del >> dst;
//        cout << src << " : " << dst << endl;
        /* Source */
        VectorOfString elements = split(src, '-');
        SPtrNode srcNode = std::shared_ptr<Node>(new Node());
        srcNode->name = std::move(elements[0]);
        srcNode->id = std::atoi(elements[1].c_str());
        srcNode->type = ElementType::Node;
        /* Destiny */
        elements = split(dst, '-');
        SPtrNode dstNode =  std::shared_ptr<Node>(new Node());
        dstNode->name = std::move(elements[0]);
        dstNode->id = std::atoi(elements[1].c_str());
        dstNode->type = ElementType::Node;
        /* Link */
        SPtrLink link =  std::shared_ptr<Link>(new Link());
        link->name = "Link";
        link->id = ++linkID;
        link->src = srcNode;
        link->dst = dstNode;
        link->type = ElementType::Link;
        srcNode->downstreamLinks.emplace_back(link);
        dstNode->upstreamLinks.emplace_back(link);
        /* Updating results */
        result.emplace_back(srcNode);
        result.emplace_back(link);
        result.emplace_back(dstNode);
    }
    return result;
}

VectorOfNodes filterByEnabledNodes(const VectorOfElements &elements)
{
    VectorOfNodes result;
    for (SPtrElement element: elements)
    {
        if (element->type == ElementType::Node)
        {
            SPtrNode node = std::dynamic_pointer_cast<Node>(element);
            result.emplace_back(node);
        }
    }
    return result;
}

VectorOfElements levelOrder(const VectorOfElements &elements)
{
    VectorOfElements result;
    std::map<unsigned int, bool> mapId;
    VectorOfNodes nodes = filterByEnabledNodes(elements);
    result.reserve(result.size());
    std::queue<SPtrNode> q;
    for (auto node: nodes)
    {
        if (node->getUpstreamLinks().size() == 0)
        {
            q.push(node);
        }
    }
    while (!q.empty())
    {
        SPtrNode node = q.front();
        auto it = mapId.find(node->getId());
        if (it == mapId.end())
        {
            result.emplace_back(node);
            mapId[node->getId()] = true;
        }
        q.pop();
        for (auto link: node->getDownstreamLinks())
        {
            auto it = mapId.find(link->getDownstream()->getId());
            if (it == mapId.end()) q.push(link->getDownstream());
        }
    }
    return result;
}
