%   File:       Xbee_communication.m
%   Author:		Matthew Haywood
%   Date:		10/13/2015
%   Description: 
%       Show how to comunicate to a micro controller using an XBee

       %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       %                                                      %
       %                                                      %
       %     ..###########.                .###########..     %
       %   :###############.              .###############:   %
       %   :###########''''                ''''###########:   %
       %    '##########.                      .###########'   %
       %     '##########.                    .##########'     %
       %       '#########.                  .#########'       %
       %               ****..            ...****              %
       %                                                      %
       %                         .##.                         %
       %                        :####:                        %
       %                      .-:####:-.                      %
       %                         '::'                         %
       %                                                      %
       %                                                      %
       %         $$$$$$    $$$$$$    $$$$$$    $$$$$$         %
       %        $$$$$$$$  $$$$$$$$  $$$$$$$$  $$$$$$$$        %
       %        $$$$$$$$  $$$$$$$$  $$$$$$$$  $$$$$$$$        %
       %        $$$$$$$$  $$$$$$$$  $$$$$$$$  $$$$$$$$        %
       %         $$$$$$    $$$$$$    $$$$$$    $$$$$$         %
       %                                                      %
       %                                                      %
       %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
clc
clear
% close any previously open com ports 
previous = instrfind('Type','serial');
if(~isempty(previous))
    fclose(previous);
end
x=10;
% Open a serial connection
% You will need to change COM3 to what ever com port your XBee is on
xbeeCom = serial('COM9', 'BaudRate', 9600, 'DataBits', 8, 'Parity', 'none',...
    'StopBits', 1, 'Timeout',5000);
pause(0.5);
% open communication port
fopen(xbeeCom);
pause(0.5);
while x ~= 0
    % prompt for the user
    fprintf ('In this example an XBee will be used to interface matlab with a Teensy\n')
    fprintf ('\tHere are the some command options:\n')
    fprintf ('\t\t1) Turn an LED on or off\n')
    fprintf ('\t\t2) Read an analog input\n')
    fprintf ('\t\t3) Turn an LED on or off\n')
    fprintf ('\t\t0) To Exit\n')
    
    prompt = 'Please enter a number for your command ';
    % request user input note that user can only enter a number
    x = input(prompt);
    clc;
    % switch case to switch between user selected input to add more
    % functionality just add another case
    switch x
        case 1
            % send comand to XBee
            fprintf(xbeeCom,'a');
            %provide user with feedback
            fprintf('You have selected Option 1\n')
            fprintf('\tThe LED should change states\n')
        case 2
             % send comand to XBee
            fprintf(xbeeCom,'d');
            print(xbeeCom,'30');
            % wait for the ~ charecter 
            %while fscanf(xbeeCom,'%c',1)~='~'
            %end
            % get analog voltage reading 
            %analogValue = fgets(xbeeCom);
            %analogDbleValue = str2double(analogValue);
             %provide user with feedback
            %fprintf('You have selected Option 2\n')
            %fprintf('\tVoltage Reading: %0.2f V\n',analogDbleValue)
        case 3
             % send comand to XBee
            fprintf(xbeeCom,'v');
    end
    % give the user a chance to read the feedback
    input('press enter to continue')
    clc;
end
%close com port 
fclose(xbeeCom);
delete(xbeeCom);