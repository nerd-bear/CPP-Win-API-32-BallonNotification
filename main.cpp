    /**
     * @brief Creates a Windows API notification using the Win32 API.
     *
     * This function creates and displays a notification in the Windows system tray.
     * The notification includes a title, a message, and an icon, and can be customized
     * to represent different types of notifications such as information, error, warning, or none.
     *
     * @param _title The title of the notification. This is a string that will be displayed as the notification's title.
     * @param _message The message of the notification. This is the content text of the notification.
     * @param _type The type of the notification. It is an integer that defines the icon and behavior of the notification:
     *        - 0: Information notification (default)
     *        - 1: Error notification
     *        - 2: Warning notification
     *        - 3: No icon notification
     *        If an invalid type is provided, the function will print an error message and terminate the program.
     *
     * @note The function internally uses the Win32 `Shell_NotifyIconW` function to add and modify the notification.
     * 
     * @warning The function calls `exit(1)` if an invalid notification type is passed. This will terminate the program.
     *
     * @details
     * - The notification is configured using a `NOTIFYICONDATAW` structure, which is filled with the appropriate information
     *   based on the provided parameters.
     * - The notification's icon is loaded using the `LoadIcon` function with the `IDI_INFORMATION` icon.
     * - The title and message strings are converted to wide strings (`std::wstring`) using a utility function (`Utils::StringToWString`).
     * - The notification's tooltip and other text fields are set using the `StringCchCopyW` function to ensure buffer safety.
     * - The notification will be displayed for 2000 milliseconds (2 seconds) before disappearing.
     * 
     * @note The function does not handle the notification's window handle (`hWnd`) and uses `NULL` for it. If the notification
     *       needs to interact with a specific window, this would need to be modified.
     */
    void CreateWinAPI32BallonNotification(std::string _title, std::string _message, int _type = 0)
    {
        HINSTANCE _hInstance = GetModuleHandle(NULL);
        NOTIFYICONDATAW _nid = {};
        _nid.cbSize = sizeof(NOTIFYICONDATAW);
        _nid.hWnd = NULL;

        switch (_type)
        {
            case 0:
                _nid.uFlags = NIF_INFO | NIF_ICON | NIF_TIP;  
                _nid.dwInfoFlags = NIIF_INFO;  
                _nid.uID = 1001;
                break;

            case 1:
                _nid.uFlags = NIF_INFO | NIF_ICON | NIF_TIP;  
                _nid.dwInfoFlags = NIIF_ERROR; 
                _nid.uID = 1002;
                break;

            case 2:
                _nid.uFlags = NIF_INFO | NIF_ICON | NIF_TIP;  
                _nid.dwInfoFlags = NIIF_WARNING;
                _nid.uID = 1003;
                break;
            
            case 3:
                _nid.uFlags = NIF_INFO | NIF_ICON | NIF_TIP;  
                _nid.dwInfoFlags = NIIF_NONE; 
                _nid.uID = 1004;
                break;

            default:
                std::cout << "Unknown Notification type!";
                exit(1);
        }

        _nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);

        std::wstring _safeTitle = Utils::StringToWString(_title);
        std::wstring _safeTitle = Utils::StringToWString(_message);

        // Directly assigning wide strings to test the notification behavior
        StringCchCopyW(_nid.szTip, ARRAYSIZE(_nid.szTip), L"My App Notification"); // Tooltip text
        StringCchCopyW(_nid.szInfo, ARRAYSIZE(_nid.szInfo), _safeTitle.c_str());
        StringCchCopyW(_nid.szInfoTitle, ARRAYSIZE(_nid.szInfoTitle), _safeTitle.c_str());

        _nid.uTimeout = 2000;

        Shell_NotifyIconW(NIM_ADD, &_nid); // Use the Unicode version of the function
        Shell_NotifyIconW(NIM_MODIFY, &_nid); // Use the Unicode version of the function
    }  
