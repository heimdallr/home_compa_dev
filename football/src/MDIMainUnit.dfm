object fmMDIMain: TfmMDIMain
  Left = 298
  Top = 118
  Width = 1032
  Height = 992
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  Caption = #1060#1091#1090#1073#1086#1083
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  OldCreateOrder = False
  OnClose = FormClose
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object sbMain: TStatusBar
    Left = 0
    Top = 943
    Width = 1024
    Height = 19
    Panels = <
      item
        Width = 200
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object alMain: TActionList
    Left = 984
    Top = 8
    object actExit: TAction
      Caption = 'actExit'
      ShortCut = 32856
      OnExecute = actExitExecute
    end
    object actChangeChamp: TAction
      Caption = 'actChangeChamp'
      ShortCut = 32835
      OnExecute = actChangeChampExecute
    end
  end
  object Timer: TTimer
    Interval = 200
    OnTimer = TimerTimer
    Left = 12
    Top = 80
  end
end
