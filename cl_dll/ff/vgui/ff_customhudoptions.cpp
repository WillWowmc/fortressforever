#include "cbase.h"
#include "ff_customhudoptions.h"

// memdbgon must be the last include file in a .cpp file!!! 
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Populate all the menu stuff
//-----------------------------------------------------------------------------
CFFCustomHudOptions::CFFCustomHudOptions(Panel *parent, char const *panelName) : BaseClass(parent, panelName)
{
	m_pPositionPresets = new CFFCustomHudPositionPresets(this, "CustomHudPositionPresets", "Position");
	m_pArrangementPresets = new CFFCustomHudArrangementPresets(this, "CustomHudArrangementPresets", "Arrangement");
	m_pStylePresets = new CFFCustomHudStylePresets(this, "CustomHudStylePresets", "Style");
	m_pAssignPresets = new CFFCustomHudAssignPresets(this, "CustomHudAssignPresets", m_pStylePresets, m_pArrangementPresets, m_pPositionPresets);

	m_pPropertyPages = new PropertySheet(this, "CustomHudPages", true);

	m_pPropertyPages->AddPage(m_pAssignPresets, "#GameUI_AssignPresets");
	m_pPropertyPages->AddPage(m_pPositionPresets, "#GameUI_PositionPresets");
	m_pPropertyPages->AddPage(m_pArrangementPresets, "#GameUI_ArrangementPresets");
	m_pPropertyPages->AddPage(m_pStylePresets, "#GameUI_StylePresets");
	m_pPropertyPages->SetActivePage(m_pAssignPresets);
	m_pPropertyPages->SetDragEnabled(false);
		
	m_pPositionPresets->AddActionSignalTarget( this );
	m_pArrangementPresets->AddActionSignalTarget( this );
	m_pStylePresets->AddActionSignalTarget( this );
	
	LoadControlSettings("resource/ui/FFOptionsSubCustomHud.res");
}

void CFFCustomHudOptions::OnActivatePage(KeyValues* data)
{
	if(Q_stricmp(data->GetString("Page"),"Arrangement"))
	{
		m_pPropertyPages->SetActivePage(m_pArrangementPresets);
	}
}

void CFFCustomHudOptions::OnActivatePositionPage(KeyValues* data)
{
	m_pPropertyPages->SetActivePage(m_pPositionPresets);
}
void CFFCustomHudOptions::OnActivateArrangmentPage(KeyValues* data)
{
	m_pPropertyPages->SetActivePage(m_pArrangementPresets);
}
void CFFCustomHudOptions::OnActivateStylePage(KeyValues* data)
{
	m_pPropertyPages->SetActivePage(m_pStylePresets);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CFFCustomHudOptions::AllowChanges(bool state)
{

}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CFFCustomHudOptions::Apply()
{
	m_pAssignPresets->Apply();
	m_pPositionPresets->Apply();
	m_pArrangementPresets->Apply();
	m_pStylePresets->Apply();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CFFCustomHudOptions::Load()
{
	m_pAssignPresets->Load();
	m_pPositionPresets->Load();
	m_pArrangementPresets->Load();
	m_pStylePresets->Load();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CFFCustomHudOptions::Reset()
{
	m_pAssignPresets->Reset();
	m_pPositionPresets->Reset();
	m_pArrangementPresets->Reset();
	m_pStylePresets->Reset();
}