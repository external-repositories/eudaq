#ifndef EUDAQ_INCLUDED_PluginManager
#define EUDAQ_INCLUDED_PluginManager

#include "DataConverterPlugin.hh"
#include "DetectorEvent.hh"

#include <string>
#include <map>

namespace eudaq {

  class DLLEXPORT PluginManager {

  public:
    using timeStamp_t = DataConverterPlugin::timeStamp_t;
    typedef DataConverterPlugin::t_eventid t_eventid;

    void RegisterPlugin(DataConverterPlugin *plugin);
    static PluginManager &GetInstance();

    static unsigned GetTriggerID(const Event &);
    static timeStamp_t GetTimeStamp(const Event &, size_t index);
    static size_t GetTimeStamp_size(const Event &);
    static int IsSyncWithTLU(eudaq::Event const & ev, eudaq::Event const & tlu);
    static t_eventid getEventId(eudaq::Event const & ev);

    static void setCurrentTLUEvent(eudaq::Event & ev, eudaq::TLUEvent const & tlu);
    static void Initialize(const DetectorEvent &);
    static void InitializeSubEvent(const Event&, const Configuration&);
    static lcio::LCRunHeader * GetLCRunHeader(const DetectorEvent &);
    static StandardEvent ConvertToStandard(const DetectorEvent &);
    static std::shared_ptr<StandardEvent> ConvertToStandard_ptr(const DetectorEvent &);
    static lcio::LCEvent * ConvertToLCIO(const DetectorEvent &);

    static void ConvertStandardSubEvent(StandardEvent &, const Event &);
    static void ConvertLCIOSubEvent(lcio::LCEvent &, const Event &);


    static std::shared_ptr<eudaq::Event> ExtractEventN(std::shared_ptr<eudaq::Event>, size_t NumberOfROF);
    static unsigned getUniqueIdentifier(const Event &);
    static bool isTLU(const Event&);

    static size_t GetNumberOfEvents(const eudaq::Event& pac);

    /** Get the correct plugin implementation according to the event type.
     */
    DataConverterPlugin &GetPlugin(t_eventid eventtype);
    DataConverterPlugin &GetPlugin(const Event &event);

  private:
    /** The map that correlates the event type with its converter plugin.
     */
    std::map<t_eventid, DataConverterPlugin *> m_pluginmap;

    PluginManager() {}
    PluginManager(PluginManager const &) {}
    class _dummy;
    friend class _dummy; // Silence superfluous warnings in some gcc versions
  };

} // namespace eudaq

#endif // EUDAQ_INCLUDED_PluginManager
