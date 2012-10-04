object fmGetString: TfmGetString
  Left = 602
  Top = 216
  Width = 791
  Height = 102
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  AutoSize = True
  Caption = 'fmGetString'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  DesignSize = (
    783
    72)
  PixelsPerInch = 96
  TextHeight = 13
  object eVal: TEdit
    Left = 0
    Top = 0
    Width = 783
    Height = 72
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -55
    Font.Name = 'Georgia'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Text = #1040' '#1090#1091#1090' '#1090#1077#1082#1089#1090'! 9667'
  end
  object alMain: TActionList
    Left = 568
    Top = 4
    object actOk: TAction
      Caption = 'actOk'
      ShortCut = 16397
      OnExecute = actOkExecute
    end
    object actCancel: TAction
      Caption = 'actCancel'
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
  end
end
