#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "GitCB.h"
#include"CommitmDialog.h"
#include <loggers.h>
#include"CloneDialog.h"
#include"BranchDialog.h"
// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<GitCB> reg(_T("GitCB"));
}

// events handling
BEGIN_EVENT_TABLE(GitCB, cbPlugin)
    // add any events you want to handle here
END_EVENT_TABLE()

// constructor
GitCB::GitCB()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("GitCB.zip")))
    {
        NotifyMissingFile(_T("GitCB.zip"));
    }
}

// destructor
GitCB::~GitCB()
{

}

void GitCB::OnAttach()
{
	Logger *gitCBLogger = new TextCtrlLogger();
	logSlot = Manager::Get()->GetLogManager()->SetLog(gitCBLogger);
	Manager::Get()->GetLogManager()->Slot(logSlot).title = _T("Git");
	CodeBlocksLogEvent evtAdd1(cbEVT_ADD_LOG_WINDOW, gitCBLogger, Manager::Get()->GetLogManager()->Slot(logSlot).title);
	Manager::Get()->ProcessEvent(evtAdd1);
    //Manager::Get()->GetLogManager()->Log(_("init"),logSlot);
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void GitCB::OnRelease(bool appShutDown)
{

   // Manager::Get()->GetLogManager()->DeleteLog(logSlot);
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

void GitCB::BuildMenu(wxMenuBar* menuBar)
{
    wxMenu* menu=menuBar->GetMenu(menuBar->FindMenu(_("Tools")));
    wxMenu* git=new wxMenu();
    wxMenu* localrepository=new wxMenu();
    localrepository->Append(commitid,_("&commit"));

   //menuBar->Insert(menuBar->FindMenu(_("&Tools"))+1,menu,wxT("&Team"));
    localrepository->Append(pushid,_("&push"));
    git->Append(cloneid,_("&clone repository"));
    git->Append(newposid,_("&creat repository"));
    git->AppendSubMenu(localrepository,_("&current repository"));
    menu->AppendSubMenu(git,_("&Git"));
    Connect(newposid,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(GitCB::newpos));
    Connect(commitid,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(GitCB::showcommitdlg));
    Connect(cloneid,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(GitCB::showclonedlg));
    Connect(pushid,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(GitCB::showpushdlg));
   // Connect(cloneid,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(GitCB::Clone));
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    //Append any items you need in the menu...
    //NOTE: Be careful in here... The application's menubar is at your disposal.
    NotImplemented(_T("GitCB::BuildMenu()"));
}

void GitCB::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    //Some library module is ready to display a pop-up menu.
    //Check the parameter \"type\" and see which module it is
    //and append any items you need in the menu...
    //TIP: for consistency, add a separator as the first item...
    NotImplemented(_T("GitCB::BuildModuleMenu()"));
}

void GitCB::newpos(wxCommandEvent& event)
{

}

void GitCB::showcommitdlg(wxCommandEvent& event)
{
    if(!IsAttached())
        return;
    CommitmDialog dialog(Manager::Get()->GetAppWindow());
    dialog.ShowModal();
}

void GitCB::showclonedlg(wxCommandEvent& event)
{
    if(!IsAttached())
        return;
    CloneDialog dialog(Manager::Get()->GetAppWindow());
    dialog.ShowModal();
}

void GitCB::showpushdlg(wxCommandEvent& event)
{
    if(!IsAttached())
        return;
    BranchDialog dialog(Manager::Get()->GetAppWindow());
    dialog.ShowModal();
}


