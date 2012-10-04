object fmLogin: TfmLogin
  Left = 818
  Top = 230
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1082#1086#1085#1085#1077#1082#1090#1072' '#1082' '#1041#1044
  ClientHeight = 189
  ClientWidth = 384
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object pnlBtn: TPanel
    Left = 0
    Top = 147
    Width = 384
    Height = 42
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    object btnOk: TBitBtn
      Left = 136
      Top = 8
      Width = 143
      Height = 25
      Action = actOk
      Caption = 'OK'
      TabOrder = 0
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
  end
  object pnlConnectStr: TPanel
    Left = 0
    Top = 0
    Width = 384
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object gbHost: TGroupBox
      Left = 0
      Top = 0
      Width = 262
      Height = 49
      Align = alLeft
      Caption = #1057#1077#1088#1074#1077#1088
      TabOrder = 0
      object pnlHost: TPanel
        Left = 2
        Top = 15
        Width = 258
        Height = 32
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 0
        DesignSize = (
          258
          32)
        object eHost: TEdit
          Tag = 1
          Left = 4
          Top = 4
          Width = 249
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          Text = 'eHost'
          OnChange = eChange
          OnKeyPress = eKeyPress
        end
      end
    end
    object gbDatabaseName: TGroupBox
      Left = 262
      Top = 0
      Width = 122
      Height = 49
      Align = alClient
      Caption = #1041#1072#1079#1072' ('#1087#1091#1090#1100' '#1080#1083#1080' '#1072#1083#1080#1072#1089')'
      TabOrder = 1
      object pnaDatabaseName: TPanel
        Left = 2
        Top = 15
        Width = 118
        Height = 32
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 0
        DesignSize = (
          118
          32)
        object eDatabaseName: TEdit
          Tag = 2
          Left = 4
          Top = 4
          Width = 109
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          Text = 'eDatabaseName'
          OnChange = eChange
          OnKeyPress = eKeyPress
        end
      end
    end
  end
  object pnlUserPwdTop: TPanel
    Left = 0
    Top = 49
    Width = 384
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object gbUser: TGroupBox
      Left = 0
      Top = 0
      Width = 262
      Height = 49
      Align = alLeft
      Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100
      TabOrder = 0
      object pnlUser: TPanel
        Left = 2
        Top = 15
        Width = 258
        Height = 32
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 0
        DesignSize = (
          258
          32)
        object eUser: TEdit
          Tag = 4
          Left = 4
          Top = 4
          Width = 249
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          Text = 'eUser'
          OnChange = eChange
          OnKeyPress = eKeyPress
        end
      end
    end
    object gbPwd: TGroupBox
      Left = 262
      Top = 0
      Width = 122
      Height = 49
      Align = alClient
      Caption = #1055#1072#1088#1086#1083#1100
      TabOrder = 1
      object pnlPwd: TPanel
        Left = 2
        Top = 15
        Width = 118
        Height = 32
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 0
        DesignSize = (
          118
          32)
        object ePwd: TEdit
          Tag = 8
          Left = 4
          Top = 4
          Width = 109
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          PasswordChar = '#'
          TabOrder = 0
          Text = 'ePwd'
          OnChange = eChange
          OnKeyPress = eKeyPress
        end
      end
    end
  end
  object pnlUserPwdBottom: TPanel
    Left = 0
    Top = 98
    Width = 384
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    DesignSize = (
      384
      49)
    object cbSavePwd: TCheckBox
      Left = 262
      Top = 4
      Width = 115
      Height = 17
      TabStop = False
      Alignment = taLeftJustify
      Anchors = [akTop, akRight]
      BiDiMode = bdLeftToRight
      Caption = #1047#1072#1087#1086#1084#1085#1080#1090#1100' '#1087#1072#1088#1086#1083#1100
      ParentBiDiMode = False
      TabOrder = 1
    end
    object gbCType: TGroupBox
      Left = 0
      Top = 0
      Width = 262
      Height = 49
      Align = alLeft
      Caption = #1050#1086#1076#1080#1088#1086#1074#1082#1072
      TabOrder = 0
      object pnlCType: TPanel
        Left = 2
        Top = 15
        Width = 258
        Height = 32
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 0
        DesignSize = (
          258
          32)
        object eCType: TEdit
          Tag = 16
          Left = 4
          Top = 4
          Width = 249
          Height = 21
          Anchors = [akLeft, akTop, akRight, akBottom]
          TabOrder = 0
          Text = 'eCType'
          OnChange = eChange
          OnKeyPress = eKeyPress
        end
      end
    end
  end
  object alMain: TActionList
    Left = 300
    Top = 116
    object actOk: TAction
      Caption = 'OK'
      ShortCut = 16397
      OnExecute = actOkExecute
    end
    object actCancel: TAction
      Caption = #1042#1099#1093#1086#1076
      ShortCut = 8219
      OnExecute = actCancelExecute
    end
  end
end
