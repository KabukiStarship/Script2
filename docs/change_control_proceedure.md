# Change Control Procedure

The Change control procedure ensures that train wrecks don't happen when Major or Minor changes are made to the code base. The extra steps required to implement the procedure are in your best interests to comply with because they were invented because of some really painful and embarrassing train wrecks.

1. The Change Request ticket shall be added to the Changes project Kanban board by submitting an Issue Ticket that shall include a one-sentence Mission statement for the Title along with Problem, Solution, Cost, and Benefits analyses and, if needed, further Mission Details that clarify the one-sentence Mission statement.
2. When enough changes have been proposed and the work schedule allows, the Changes Request tickets shall be prioritized based on the order of importance using a cost-benefit analysis by the Change control board.
3. If a Change Request has been approved by the Change control board, the Change Request ticket shall be moved into the In Progress Changes kanban board, a Change Response Document shall be created by submitting an Issue ticket for each Change Option with sections for the option's Proposed Solution, Proposed Timeline, Impacts to the Project, and an Expiration Date for Proposed Changes.
4. Once a Change option for the Change has been agreed upon by the Change control board, the Change Option ticket shall be renamed a Change ticket and marked Major Change or Minor Change before placing it into the In Progress Changes kanban board and closing competing Change option tickets.
5. All branches containing changes to files affected by the changes defined in the "Impacts to Projects" section of the Change Response shall be merged with their respective parent branches or deleted until there are no more conflicting changes to the affected files, and the Change Request ticket closed.
6. A new branch created for the Change ticket shall be created where the change shall be implemented and pass all unit tests.
7. Finished changes shall be reviewed by the Change control board using a Pull Request, at which time the Change ticket shall be moved into the Reviewing Kanban board.
8. If the Pull Request contains any leftover artifacts from the Change or improper unit test coverage, the request shall be denied, requiring steps 7 and 8 to be repeated as many time as necessary.
9. After a successful Pull Request, the Change ticket shall be moved into the Done Changes kanban board and closed.
